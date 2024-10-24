#include <SPI.h>
#include <Wire.h>
#include "DHTesp.h"
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

DHTesp dht;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS);

float humidity = 0;
float temperature = 0;

void Set_SH1106();
void Read_DHT11();

void setup() 
{
  Serial.begin(115200);
  Set_SH1106();
  dht.setup(DHTPIN, DHTesp::DHTTYPE); 
}

void loop() 
{
  Read_DHT11();
  delay(1000);
}

void Read_DHT11()
{
  humidity = dht.getHumidity();
  temperature = dht.getTemperature();

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("Loi Tran!");

  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print("Temperature: ");
  display.print(temperature);
  display.println(" C");

  display.setCursor(0, 45);
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");
  display.display();
}

void Set_SH1106()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  display.setTextColor(SSD1306_WHITE);
}