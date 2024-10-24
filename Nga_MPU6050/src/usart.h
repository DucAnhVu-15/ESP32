#ifndef __USART_H__
#define __USART_H__

#include <Arduino.h>
#include <HardwareSerial.h>

extern HardwareSerial MySerial; // define a Serial for UART1
extern const int Rx_1;
extern const int Tx_1;

extern String received_data;

void Usart_setup();
void Usart_send(uint8_t data);

#endif