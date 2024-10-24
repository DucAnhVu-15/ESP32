
// void setup(){

// }

// void loop(){
//   if(flag){
//     _vr_setup_time = 1;
//     _vr_setup_alarm = 1;
//     flag = 0;
//   }
//   setup_time();
//   setup_Alarm();
// }

// void setup_time(){
//   if(_vr_setup_time){
//     //
//     _vr_setup_time = 0;
//   }
// }

// void setup_Alarm(){
//   if(_vr_setup_alarm){
//     //
//     _vr_setup_alarm = 0;
//   }
// }

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <Wire.h>

hw_timer_t *timer1 = NULL;

LiquidCrystal_I2C lcd(0x27, 20, 4);
unsigned int but_setup = 1;
unsigned int but_up = 1;
unsigned int but_down = 1;
unsigned int but_alarm = 1;
unsigned int flag = 0;
unsigned int state = 0;
uint32_t sec = 0, sec_alarm = 0;
int minute = 0, minute_alarm = 0;
int hour = 0, hour_alarm = 6;
int cnt = 0;
int cnt1 = 0, cnt2 = 0;
int cnt_sec = 0;
unsigned int check_setup = 0, check_alarm = 0;
unsigned int potAlarm = 0;
uint8_t btn_stt_setup_old = 1, btn_stt_setup_new = 0;
uint8_t btn_stt_setup_old1 = 1, btn_stt_setup_new1 = 0;

void IRAM_ATTR Readbut()
{
  flag = 1;
}

void setup()
{
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  // lcd.print("Time");

  Serial.begin(9600);

  pinMode(25, INPUT);
  pinMode(26, INPUT);
  pinMode(27, INPUT);

  timer1 = timerBegin(1, 8000, true); // Use timer 1 with a prescaler of 80
  timerAttachInterrupt(timer1, &Readbut, true);
  timerAlarmWrite(timer1, 1000, true); // 1 second interval
  timerAlarmEnable(timer1);

  pinMode(17, OUTPUT);
}

void displayTime();
void RunTime();
void TimeSetup();
void displayTime_Alarm();
void Alarm();

void loop()
{
  if (flag)
  {
    TimeSetup();
    Alarm();
    if (check_alarm == 1)
    {
      if (hour_alarm == hour && minute_alarm == minute)
      {
        digitalWrite(17, HIGH);
      }
      else
      {
        digitalWrite(17, LOW);
        check_alarm = 0;
      }
        
    }
    flag = 0;
  }
}

// Hien thi dong ho

void displayTime()
{
  lcd.setCursor(0, 1);
  // Print the time in "hh:mm:ss" format with leading zeros
  lcd.print((hour < 10 ? "0" : ""));
  lcd.print(hour);
  lcd.print(":");
  lcd.print((minute < 10 ? "0" : ""));
  lcd.print(minute);
  lcd.print(":");
  lcd.print((sec < 10 ? "0" : ""));
  lcd.print(sec);
}

// Chay dong ho
void RunTime()
{
  cnt_sec++;
  if (cnt_sec == 10)
  {
    sec++;
    cnt_sec = 0;
  }

  if (sec == 60)
  {
    sec = 0;
    minute++;

    if (minute == 60)
    {
      minute = 0;
      hour++;

      if (hour > 23)
      {
        hour = 0;
      }
    }
  }
}

// Cai dat gio

void TimeSetup()
{
  displayTime();
  RunTime();

  btn_stt_setup_old1 = but_setup;
  but_setup = digitalRead(25);
  if (btn_stt_setup_old1 == 1 && but_setup == 0)
  {
    but_setup = 1;
    cnt++;
    delay(10);
  }

  Serial.println("Flag cnt: " + String(cnt));
  but_up = digitalRead(26);
  but_down = digitalRead(27);

  if (cnt == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print("Time Set Up");
    displayTime();
  }
  else if (cnt == 2)
  {
    if (but_up == 0)
    {
      hour++;
      if (hour > 23)
      {
        hour = 0;
      }
      delay(10);
      displayTime(); // Update displayed time after changing the hour
    }
    if (but_down == 0) //*
    {
      hour--;
      if (hour < 0)
      {
        hour = 23;
      }
      delay(10);
      displayTime(); // Update displayed time after changing the hour
    }
  }
  else if (cnt == 3)
  {
    if (but_up == 0)
    {
      minute++;
      if (minute > 59)
      {
        minute = 0;
        hour++;
        if (hour > 23)
        {
          hour = 0;
        }
      }
      delay(10);
      displayTime(); // Update displayed time after changing the minute
    }
    if (but_down == 0) //*
    {
      minute--;
      if (minute < 0)
      {
        minute = 59;
        hour--;
        if (hour < 0)
        {
          hour = 23;
        }
      }
      delay(10);
      displayTime(); // Update displayed time after changing the minute
    }
  }
  else if (cnt == 4)
  {
    cnt = 0;
    delay(10);
  }
}

// Display_Alarm

void displayTime_Alarm()
{
  lcd.setCursor(0, 3);
  // Print the time in "hh:mm:ss" format with leading zeros
  lcd.print((hour_alarm < 10 ? "0" : ""));
  lcd.print(hour_alarm);
  lcd.print(":");
  lcd.print((minute_alarm < 10 ? "0" : ""));
  lcd.print(minute_alarm);
  lcd.print(":");
  lcd.print((sec_alarm < 10 ? "0" : ""));
  lcd.print(sec_alarm);
}

// Bao Thuc

void Alarm()
{
  btn_stt_setup_old = but_alarm;
  but_alarm = digitalRead(18);
  if (btn_stt_setup_old == 1 && but_alarm == 0)
  {
    but_alarm = 1;
    cnt1++;
    delay(10);
  }
  Serial.println("Flag cnt1: " + String(cnt1));

  but_up = digitalRead(26);
  but_down = digitalRead(27);

  if (cnt1 == 1)
  {
    lcd.setCursor(0, 2);
    lcd.print("Time Alarm");
    displayTime_Alarm();
  }
  else if (cnt1 == 2)
  {
    if (but_up == 0)
    {
      hour_alarm++;
      if (hour_alarm > 23)
      {
        hour_alarm = 0;
      }
      delay(10);
      displayTime_Alarm();
    }

    if (but_down == 0)
    {
      hour_alarm--;
      if (hour_alarm < 0)
      {
        hour_alarm = 23;
      }
      delay(10);
      displayTime_Alarm();
    }
  }
  else if (cnt1 == 3)
  {
    if (but_up == 0)
    {
      minute_alarm++;
      if (minute_alarm > 59)
      {
        minute_alarm = 0;
      }
      displayTime_Alarm();
    }

    if (but_down == 0)
    {
      minute_alarm--;
      if (minute_alarm < 0)
      {
        minute_alarm = 59;
      }
      delay(10);
      displayTime_Alarm();
    }
  }
  else if (cnt1 == 4)
  {
    cnt1 = 0;
    check_alarm = 1;
    delay(10);
  }
}
