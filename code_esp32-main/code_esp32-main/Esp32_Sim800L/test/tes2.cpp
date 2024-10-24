/* ======================================== */
/* SIM800 */
/* ======================================== */
#include <aht_sim800.h>
#define MODEM_RX 16
#define MODEM_TX 17
#define uart Serial2

AHT_GSM *gsmMaster = new AHT_GSM(&uart);
AHT_GSM *gsm;
GSM_TYPE gsmType;
bool gsmOk = false;

char number_phone[]="+84969656498";
//char number_phone[]="0969656498";
char messenger[]="Vu Thi Thu Ha, Thuy Duong - Thai Thuy - Thai Binh.";

void SIM800x_SendSMS(char NumPhone[], char Text[]){
	Serial.printf("AT+CMGS=\"%s\"\r\n",NumPhone);
	delay(500);
	Serial.printf("%s", messenger);
	delay(500);
	Serial.printf("%c",0x1a);
}

void setup() 
{
    Serial.begin(115200);
	uart.begin(115200);
    delay(1000);

	Serial.printf("AT\r\n");
	delay(1000);
	Serial.printf("AT+IPR= 9600\r\n");
	delay(500);
	Serial.printf("AT+CMGF=1\r\n"); 
	delay(500);
	Serial.printf("AT+CNMI=2,1,0,0,0\r\n");   
	delay(500);   
	SIM800x_SendSMS(number_phone,messenger);
}

void loop()
{
    // if(!gsmOk)
    // {
    //     Serial.println("can't detect gsm module");
    //     delay(5000);
    //     return;
    // }

    if(uart.available())
    {
        Serial.write(uart.read());
    }
    if(Serial.available())
    {
        char c = Serial.read();
        Serial.write(c);
        uart.write(c);
    }
}