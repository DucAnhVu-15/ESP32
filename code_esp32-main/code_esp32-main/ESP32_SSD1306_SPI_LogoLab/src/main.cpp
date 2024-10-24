#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI   23
#define OLED_CLK    18
#define OLED_DC     16
#define OLED_CS     5
#define OLED_RESET  17

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

const unsigned char epd_bitmap_4__1_ [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x0f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x03, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x07, 0xf0, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xe3, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x07, 0xff, 0x80, 0x07, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xf1, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x07, 0xff, 0xf8, 0x00, 0xff, 0xfe, 0x00, 0x3f, 0xff, 0xf3, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0x00, 0x1f, 0xf8, 0x03, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xe0, 0x07, 0xc0, 0x1f, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xfc, 0x00, 0x00, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0x80, 0x07, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0x3f, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0x03, 0x00, 0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xf8, 0x1f, 0xe0, 0x3f, 0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xf0, 0x7f, 0xf8, 0x0f, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xc1, 0x94, 0x28, 0x03, 0xff, 0xc0, 0x07, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0x06, 0x00, 0x00, 0x00, 0xff, 0xc8, 0x3f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xe0, 0x3c, 0x38, 0x00, 0x00, 0x40, 0x7f, 0x3f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf0, 0x08, 0xf8, 0x00, 0x00, 0x58, 0x1e, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfc, 0x03, 0xf8, 0x00, 0x00, 0x5e, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xf8, 0x00, 0x00, 0x5f, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x78, 0x00, 0x00, 0x7f, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x60, 0x38, 0x00, 0x00, 0x5e, 0x10, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf9, 0xf8, 0x06, 0x00, 0x00, 0x78, 0x78, 0x3f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x03, 0xfe, 0x02, 0x00, 0x00, 0x60, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0x01, 0xff, 0x80, 0xd5, 0xab, 0x83, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xc0, 0x00, 0xff, 0xe0, 0x3f, 0xfe, 0x0f, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xf8, 0x0f, 0xf8, 0x3f, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xc0, 0x00, 0xff, 0xfe, 0x01, 0xc0, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf0, 0x03, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0x00, 0x80, 0x7f, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xcf, 0xff, 0xff, 0xf8, 0x03, 0xf0, 0x1f, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xc0, 0x1f, 0xfe, 0x01, 0xff, 0xe0, 0x01, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x9f, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0xe0, 0x3f, 0xc0, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x9f, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xfc, 0x01, 0xc0, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x8f, 0xfe, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x80, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x01, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfc, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xe0, 0x30, 0xe3, 0x80, 0xe0, 0x30, 0x1e, 0x03, 0xc0, 0xc0, 0x7f, 0xfc, 0x3c, 0x38, 0x1c, 0x03, 
	0xe0, 0x20, 0xc1, 0x00, 0x60, 0x10, 0x04, 0x00, 0x80, 0x40, 0x1f, 0xf8, 0x1c, 0x30, 0x00, 0x03, 
	0xe1, 0xe0, 0x41, 0x0c, 0x21, 0xe0, 0x84, 0x30, 0x87, 0xc2, 0x1f, 0xf8, 0x1c, 0x21, 0x87, 0x0f, 
	0xe0, 0x60, 0x01, 0x00, 0x60, 0x20, 0x84, 0x30, 0x80, 0xc2, 0x1f, 0xf8, 0x1c, 0x21, 0x87, 0x0f, 
	0xe0, 0x20, 0x01, 0x00, 0x20, 0x20, 0x84, 0x30, 0x80, 0xc2, 0x18, 0x30, 0x0c, 0x21, 0x87, 0x0f, 
	0xe1, 0xe0, 0x01, 0x0c, 0x21, 0xe0, 0x84, 0x30, 0x87, 0xc2, 0x18, 0x30, 0x0c, 0x21, 0x87, 0x0f, 
	0xe1, 0xe2, 0x11, 0x00, 0x20, 0xe0, 0x04, 0x00, 0x83, 0xc0, 0x1f, 0xe0, 0x0c, 0x20, 0x87, 0x0f, 
	0xe0, 0x22, 0x11, 0x00, 0x60, 0x10, 0x0c, 0x01, 0x80, 0x40, 0x3f, 0xe1, 0x84, 0x30, 0x0f, 0x0f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x8b, 0x8c, 0x62, 0x18, 0xda, 0xc6, 0x78, 0x43, 0x08, 0x51, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x1b, 0x89, 0xe6, 0x06, 0x4a, 0x1c, 0x33, 0x07, 0x04, 0xd9, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x19, 0x89, 0xf6, 0x12, 0x52, 0x1e, 0x33, 0x0f, 0x3c, 0xd9, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x88, 0x8e, 0x77, 0xd8, 0xfb, 0xc6, 0x3c, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  
  // Display the logo on the OLED screen
  display.drawBitmap(0, 0, epd_bitmap_4__1_, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  display.display();
}
void loop() {
  // Your main code goes here (if any)
}
