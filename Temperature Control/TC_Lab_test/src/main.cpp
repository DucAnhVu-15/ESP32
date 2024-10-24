#include <Arduino.h>
#include <time.h>

hw_timer_t *timer = NULL;

#define senT1 26 // LM35
#define actH1 25

#define ADC_VREF_mV 4400.0 // bằng milivolt
#define ADC_RESOLUTION 4095.0

bool Matlab = true;
float Temp1, Temp2, H1 = 0.0;

float w = 0;            // Tham chiếu
float e[3] = {0, 0, 0}; // Vector lỗi
float u[2] = {0, 0};    // Vector Luật Điều Khiển
int kU = sizeof(u) / sizeof(float) - 1;
int kE = sizeof(e) / sizeof(float) - 1;
float kp, ti, td, q0, q1, q2; // Tham số của PID

// Mô hình của Hệ thống
float K = 0.76822, tau = 199.96, theta = 11.06;
int Ts = 15; // Chu kỳ Lấy mẫu
float L = theta + Ts / 2;

void Set_up(void);
float Temperature_Read(int senT); // Tính ra nhiệt độ từ LM35
float CurrentRead(int senT);      // Tính ra giá trị hiệu điện thế từ LM35
void Serial_Plotter();            // Hiển thị dữ liệu ra Serial Plotter
void SampleTime(void);            // Tính toán giá trị điều khiển PID
void update_past(float v[], int kT);
float PID_Controller(float u[], float e[3], float q0, float q1, float q2);

void IRAM_ATTR onTimer()
{
  SampleTime();
}

void setup()
{
  Set_up();
}

void loop()
{
  Temp1 = Temperature_Read(senT1);

  Serial_Plotter();
}

void Set_up(void)
{
  Serial.begin(9600);
  pinMode(senT1, INPUT);
  pinMode(actH1, OUTPUT);
  analogWrite(actH1, 0);
  analogWrite(senT1, 0);

  // Khởi tạo timer
  timer = timerBegin(0, 8000, true);
  // Đính kèm hàm ngắt cho timer
  timerAttachInterrupt(timer, &onTimer, true);
  // Ghi thời gian ngắt cho timer (150000 tương ứng với 15 giây)
  timerAlarmWrite(timer, 150000, true);
  // Kích hoạt timer
  timerAlarmEnable(timer);

  // ******* TINH CHỈNH PID ZN ******** //

  kp = (1.2 * tau) / (K * L);
  ti = 2 * L;
  td = 0.5 * L;

  // **** BỘ ĐIỀU KHIỂN PID ****** //
  q0 = kp * (1 + Ts / (2 * ti) + td / Ts);
  q1 = -kp * (1 - Ts / (2 * ti) + (2 * td) / Ts);
  q2 = (kp * td) / Ts;
}

void SampleTime(void)
{
  // Cập nhật các vector u và e
  update_past(u, kU);
  update_past(e, kE);

  // Tính toán lỗi hiện tại
  e[kE] = w - Temp1;

  // Tính toán Hành động Điều khiển PID
  u[kU] = PID_Controller(u, e, q0, q1, q2); // Max= 100, Min=0
  H1 = u[kU];

  // Áp dụng hành động điều khiển vào PWM
  analogWrite(actH1, map(H1, 0, 100, 0, 255)); // Max= 100, Min=0
}

void update_past(float v[], int kT)
{
  int i;
  for (i = 1; i <= kT; i++)
  {
    v[i - 1] = v[i];
  }
}

/*=======================    HÀM ĐIỀU KHIỂN PID  ============================*/

float PID_Controller(float u[], float e[3], float q0, float q1, float q2)
{
  float lu;
  // Điều khiển PID
  // e[2] = e(k)
  // e[1] = e(k-1)
  // e[0] = e(k-2)
  // u[0] = u(k-1)
  lu = u[0] + q0 * e[2] + q1 * e[1] + q2 * e[0]; // Luật điều khiển PID rời rạc

  // Chống quá mức (Anti - Windup)
  if (lu >= 100.0)
    lu = 100.0;

  if (lu <= 0.0)
    lu = 0.0;

  return (lu);
}

float Temperature_Read(int senT) // Tính ra nhiệt độ từ LM35
{
  // Đọc giá trị ADC từ cảm biến nhiệt độ
  int adcVal = analogRead(senT);

  float S1, aux;
  int i;
  // Bộ lọc trung bình động trên giá trị đọc ADC
  aux = 0;
  for (i = 0; i < 10; i++)
  {
    // Mỗi 10mV = 1 độ C.
    aux = aux + adcVal * (ADC_VREF_mV / ADC_RESOLUTION) / 10; // LM35
  }
  S1 = aux / 10.0;
  return (S1);
}

float CurrentRead(int senT) // Tính ra giá trị hiệu điện thế từ LM35
{
  // Đọc giá trị ADC từ cảm biến nhiệt độ
  int adcVal = analogRead(senT);

  float S1, aux;
  int i;
  // Bộ lọc trung bình động trên giá trị đọc ADC
  aux = 0;
  for (i = 0; i < 10; i++)
  {
    // Mỗi 10mV = 1 độ C.
    aux = aux + adcVal * (ADC_VREF_mV / ADC_RESOLUTION); // LM35
  }
  S1 = aux / 10.0;
  return (S1);
}

void Serial_Plotter(void)
{
  String dato, degC;
  int i, ini, fin;
  if (Serial.available())
  {
    dato = Serial.readString();
    for (i = 0; i < 10; i++)
    {
      if (dato[i] == 'S')
      {
        ini = i + 1;
        i = 10;
      }
    }
    for (i = ini; i < 10; i++)
    {
      if (dato[i] == '$')
      {
        fin = i;
        i = 10;
      }
    }

    degC = dato.substring(ini, fin);
    w = degC.toDouble();
  }

  if (Matlab)
  { // Sử dụng giao diện Matlab
    Serial.print("I");
    Serial.print(Temp1);
    Serial.print("F");
    Serial.print("I");
    Serial.print(Temp1);
    Serial.print("F");

    Serial.print("C");
    Serial.print(H1);
    Serial.print("R");
    Serial.print("C");
    Serial.print(H1);
    Serial.print("R");
    Serial.println();
  }
  else
  { // Sử dụng Serial Plotter
    Serial.println("Temperature_1(C),Heater_1(%)");
    Serial.print(Temp1);
    Serial.print(",");
    Serial.println(H1);
  }
  delay(1000);
}
