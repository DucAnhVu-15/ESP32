#include "lib_display.h"

TFT_eSPI tft = TFT_eSPI();

void TFT_Init(void)
{
    // Initialize TFT display
    tft.begin();
    tft.setRotation(3); // Adjust the rotation if needed (0, 1, 2, or 3)

    // Set up TFT pins
    tft.setPins(TFT_CLK, TFT_RST, TFT_DC, TFT_CS, TFT_MISO, TFT_MOSI);

    // Clear the screen
    tft.fillScreen(TFT_BLACK);

    // Set text color and font size
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);

    // Display a text
    tft.setCursor(10, 10);
    tft.println("Hello, ESP32!");

    // Draw a rectangle
    tft.drawRect(50, 50, 100, 100, TFT_WHITE);
}