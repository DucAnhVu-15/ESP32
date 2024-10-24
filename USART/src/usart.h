#ifndef __USART_H__
#define __USART_H__

#include <Arduino.h>
#include <HardwareSerial.h>

extern HardwareSerial MySerial; // define a Serial for UART1
extern const int Rx_2;
extern const int Tx_2;

extern String received_data;

void Usart_setup();
void Usart_receive();
void Usart_send(const char *data);
#endif