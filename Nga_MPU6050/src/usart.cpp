#include <usart.h>

HardwareSerial MySerial(1); // define a Serial for UART2
const int Rx_1 = 15;
const int Tx_1 = 16;

String received_data = "";

void Usart_setup()
{
  // initialize the Serial with specified pins
  MySerial.begin(115200, SERIAL_8N1, Rx_1, Tx_1);
}

void Usart_send(uint8_t data)
{
  MySerial.write(data); 
}
