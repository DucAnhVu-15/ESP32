#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Pin connections for ESP32
#define TFT_CLK   18
#define TFT_RST   4
#define TFT_DC    2
#define TFT_CS    5
#define TFT_SDA   23

// Create an instance of the ST7735 library
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST, TFT_CLK, TFT_SDA);

void setup() 
{
  Serial.begin(115200);
  // Initialize the TFT display
  tft.initR(INITR_BLACKTAB);  // Use this line for ST7735B displays

  // Rotate the display if required
  tft.setRotation(1);  // Uncomment this line to rotate display 90 degrees
  
  // Fill the screen with a color
  tft.fillScreen(ST7735_YELLOW);
  
  // Set text color and size
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  
  // Set the cursor position
  tft.setCursor(10, 10);
  
  // Print text
  tft.println("Hello, TFT!");
}

void loop() {
  // Nothing to do here
}
