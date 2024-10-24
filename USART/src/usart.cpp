#include <usart.h>
#include <time_uart.h>

HardwareSerial MySerial(1); // define a Serial for UART2
const int Rx_2 = 15;
const int Tx_2 = 16;

String received_data = "";

void Usart_setup()
{
  // initialize the Serial with specified pins
  MySerial.begin(115200, SERIAL_8N1, Rx_2, Tx_2);
}

void Usart_receive()
{
  while (MySerial.available() > 0)
  {
    char byteFromSerial = MySerial.read();
    received_data += byteFromSerial;
  }
  if (received_data.length() != 0)
  {
    MySerial.println("received_data: ");
    MySerial.println(received_data);
    received_data = "";
  }
}

void Usart_send(const char *data)
{
  MySerial.write(data); // Gửi dữ liệu chuỗi qua UART
}
