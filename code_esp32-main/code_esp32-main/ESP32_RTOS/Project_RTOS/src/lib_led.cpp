#include "lib_led.h"


void LED_Init()
{
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    digitalWrite(LED_RED_PIN, 1);
    digitalWrite(LED_GREEN_PIN, 1);
}

void LED_RED()
{
    digitalWrite(LED_RED_PIN, 0);
    digitalWrite(LED_GREEN_PIN, 1);
}

void LED_GREEN()
{
    digitalWrite(LED_RED_PIN, 1);
    digitalWrite(LED_GREEN_PIN, 0);
}
