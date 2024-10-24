#include "Arduino.h"

#define senT1 26 // LM35
#define actH1 25

#define ADC_VREF_mV 4400.0 // in millivolt
#define ADC_RESOLUTION 4095.0

int count = 0;

bool Matlab = false;
String dato, degC;
int i, ini, fin;
float Temp1, Temp2, H1 = 0.0;
void Set_up(void);
float Temperature_Read(int senT); // Tính ra nhiệt độ từ LM35
float CurrentRead(int senT);      // Tính ra giá trị hiệu điện thế từ LM35

void Serial_Plotter(void);
float CurrentRead(int senT);
void Set_up(void);
float Temperature_Read(int senT);

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
}

float Temperature_Read(int senT) // Tính ra nhiệt độ từ LM35
{
    // read the ADC value from the temperature sensor
    int adcVal = analogRead(senT);

    float S1, aux;
    int i;
    // Filtro de promedio movil en la lectura ADC
    aux = 0;
    for (i = 0; i < 1000; i++)
    {
        // Cứ mỗi 10mV = 1 độ C.
        aux = aux + adcVal * (ADC_VREF_mV / ADC_RESOLUTION) / 10; // LM35
                                                                  // delay(5);~
    }
    S1 = aux / 1000.0;
    return (S1);
}

float CurrentRead(int senT) // Tính ra giá trị hiệu điện thế từ LM35
{
    // read the ADC value from the temperature sensor
    int adcVal = analogRead(senT);

    float S1, aux;
    int i;
    // Filtro de promedio movil en la lectura ADC
    aux = 0;
    for (i = 0; i < 1000; i++)
    {
        // Cứ mỗi 10mV = 1 độ C.
        aux = aux + adcVal * (ADC_VREF_mV / ADC_RESOLUTION); // LM35
                                                             // delay(5);
    }
    S1 = aux / 1000.0;
    return (S1);
}

void Serial_Plotter(void)
{
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
        H1 = degC.toInt();
        analogWrite(actH1, map(H1, 0, 100, 0, 255));
    }

    if (Matlab)
    { // Usar la interfaz de Matlab
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
    }
    else
    { // Usar el Serial Plotter
        Serial.println("Temperatura_1(C),Heater_1(%)");
        Serial.print(T1);
        Serial.print(",");
        Serial.println(H1);
    }
    delay(1000);
}
