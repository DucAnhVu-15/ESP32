#include "WiFi.h"
#include <SPI.h>
#include <Wire.h>
#include "DHTesp.h"
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define DHTPIN 15     // DHT11 sensor pin
#define DHTTYPE DHT11 // DHT11 sensor type
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_MOSI 23
#define OLED_CLK  18
#define OLED_DC   19
#define OLED_CS   5
#define OLED_RST  16

const char* ssid = "LAB_2G";
const char* password = "embeddedlab";
// const char* ssid = "Wifi Vung Cao";
// const char* password = "66668888";
const char* ntpServerName = "3.asia.pool.ntp.org";
const int timeZone = 7; // GMT+7

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServerName, timeZone * 3600, 60000);
DHTesp dht;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS);

float humidity = 0;
float temperature = 0;
int count_time_wifi = 0;

void Set_NTP();
void Set_SH1106();
void Read_DHT11();
void Connect_Wifi();

void setup() 
{
  Serial.begin(115200);
  Set_SH1106();
  Connect_Wifi();
  Set_NTP();
  dht.setup(DHTPIN, DHTesp::DHTTYPE); 
}

void loop() 
{
  Read_DHT11();
}

void Read_DHT11()
{
  humidity = dht.getHumidity();
  temperature = dht.getTemperature();

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(timeClient.getDay());
  display.setCursor(80, 0);
  display.println(timeClient.getFormattedTime());

  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print("Tem:");
  display.print(temperature);
  display.println("C");

  display.setCursor(0, 40);
  display.print("Hum:");
  display.print(humidity);
  display.println("%");
  display.display();
  delay(1000);
}

void Set_SH1106()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  display.setTextColor(SSD1306_WHITE);
}

void Set_NTP()
{
  timeClient.begin();
  while(!timeClient.update()) 
  {
    timeClient.forceUpdate();
  }
}

void Connect_Wifi()
{
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED && count_time_wifi < 10) 
  {
    count_time_wifi++;
    delay(500);
  }

  if(count_time_wifi > 9)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(23, 0);
    display.println("Disconnected WIFI!");
    display.display();
  }

  if(WiFi.status() == WL_CONNECTED)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(25, 0);
    display.println("Connected WIFI!");
    display.display();
  }
  delay(2000);
}

