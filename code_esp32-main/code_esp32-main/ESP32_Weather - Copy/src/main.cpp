#include "WiFi.h"
#include "DHTesp.h"
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "SH1106.h"
#include "SH1106Ui.h"

#define DHTPIN 15       // DHT data pin is connected to GPIO 15
#define DHTTYPE DHT11   // DHT11 sensor model is used

#define OLED_RESET  17   // RESET
#define OLED_DC     16   // Data/Command
#define OLED_CS     5    // Chip select

const char* ssid = "Wifi Vung Cao";
const char* password = "66668888";

DHTesp dht;
// Uncomment one of the following based on OLED type
SH1106 display(true, OLED_RESET, OLED_DC, OLED_CS); // FOR SPI
//SH1106   display(OLED_ADDR, OLED_SDA, OLED_SDC);    // For I2C
SH1106Ui ui(&display);

void Connect_Wifi();
void Read_DHT11();
void Set_SH1106();

bool msOverlay(SH1106 *display, SH1106UiState* state);
bool drawFrame1(SH1106 *display, SH1106UiState* state, int x, int y);
// this array keeps function pointers to all frames
// frames are the single views that slide from right to left
bool (*frames[])(SH1106 *display, SH1106UiState* state, int x, int y) = {drawFrame1};
bool (*overlays[])(SH1106 *display, SH1106UiState* state)             = { msOverlay};

int count_time_wifi = 0;
float humidity = 0;
float temperature = 0;
int frameCount = 3;// how many frames are there?
int overlaysCount = 1;

void setup() 
{
  Serial.begin(115200);
  // Connect_Wifi();
  Set_SH1106();
  dht.setup(DHTPIN, DHTesp::DHTTYPE); // Connect DHT sensor
}

void loop() 
{
  humidity = dht.getHumidity();
  temperature = dht.getTemperature();
  Read_DHT11();

  int remainingTimeBudget = ui.update();
  if (remainingTimeBudget > 0) 
  {
    delay(remainingTimeBudget);
  }
}

bool msOverlay(SH1106 *display, SH1106UiState* state) 
{
    // In ra ngày tháng
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(1, 0, String(1) + "/" + String(4));
  //display->drawString(0, 0, String(now.day()) + "/" + String(now.month()));

  // In ra thời gian
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(1, 0, String(12) + ":" + String(15));
  // display->drawString(128, 0, String(now.hour()) + ":" + String(now.minute()));
  return true;
}

bool drawFrame1(SH1106 *display, SH1106UiState* state, int x, int y) 
{
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(39 + x, 14 + y, "- In Room -");

  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(1 + x, 28 + y, "Temperature: " + String(temperature) + " C");

  display->setFont(ArialMT_Plain_10);
  display->drawString(1 + x, 41 + y, "Humidity: " + String(humidity) + " %");

  return false;
}

void Set_SH1106()
{
  ui.setTargetFPS(30);
  // You can change this to
  // TOP, LEFT, BOTTOM, RIGHT
  ui.setIndicatorPosition(BOTTOM);
  // Defines where the first frame is located in the bar.
  ui.setIndicatorDirection(LEFT_RIGHT);
  // You can change the transition that is used
  // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_TOP, SLIDE_DOWN
  ui.setFrameAnimation(SLIDE_LEFT);
  // Add frames
  ui.setFrames(frames, frameCount);
  // Add overlays
  ui.setOverlays(overlays, overlaysCount);
  // Inital UI takes care of initalising the display too.
  ui.init();
  //display.flipScreenVertically();
}

void Read_DHT11()
{
  Serial.print(temperature);
  Serial.println("*C");
  Serial.print(humidity);
  Serial.println("%");
   Serial.println();
}

void Connect_Wifi()
{
  Serial.println();
  Serial.print("Connecting to WIFI: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED && count_time_wifi < 10) 
  {
    Serial.println(".");
    count_time_wifi++;
    delay(500);
  }

  if(count_time_wifi > 9)
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


/*
D17 - RES
D16 - DC
D5  - CS
D13 - D1
D14 - D0
*/