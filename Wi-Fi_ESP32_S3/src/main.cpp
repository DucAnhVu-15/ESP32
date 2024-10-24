#include <Arduino.h>
#include <wifi_mqtt.h>

void setup()
{
  WiFi_setup();
  MQTT_Connect();
}

void loop()
{
  run_mqtt();
}