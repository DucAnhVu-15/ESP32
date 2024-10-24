#include <usart.h>
#include <mqtt.h>
#include <time_uart.h>

void setup()
{
  Usart_setup();
  // WiFi_setup();
  // TimeUART_setup();
  // MQTT_Connect();
}

void loop()
{
  // Usart_send("Hello from ESP32");
  Usart_receive();
  // delay(1000);
  // run_mqtt();
}
