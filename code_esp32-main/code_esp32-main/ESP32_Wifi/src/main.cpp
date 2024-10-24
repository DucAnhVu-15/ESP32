#include <WiFi.h>


const char* ssid = "LAB_2G";
const char* password = "embeddedlab";
// const char* ssid = "Wifi Vung Cao";
// const char* password = "66668888";

int count_time = 0;

void Connect_Wifi();


void setup() 
{
  Serial.begin(115200);
  Connect_Wifi();
}

void loop() 
{
  
}

void Connect_Wifi()
{
  Serial.println();
  Serial.print("Connecting to WIFI: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED && count_time < 10) 
  {
    Serial.println(".");
    count_time++;
    delay(500);
  }

  if(count_time > 9)
  {
    Serial.println("Connect WIFI FAILD");
  }

  if(WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Connect WIFI SUCCESSFUL");
    Serial.print("IP Address of ESP32: ");
    Serial.println(WiFi.localIP());
    Serial.println();
  }
}
