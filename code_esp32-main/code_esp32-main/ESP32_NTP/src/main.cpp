#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "Wifi Vung Cao";
const char* password = "66668888";
const char* ntpServerName = "3.asia.pool.ntp.org";
const int timeZone = 7; // GMT+7

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServerName, timeZone * 3600, 60000);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  timeClient.begin();
  while(!timeClient.update()) 
  {
    timeClient.forceUpdate();
  }
}

void loop() {
  Serial.println(timeClient.getFormattedTime());
  delay(1000);
}
