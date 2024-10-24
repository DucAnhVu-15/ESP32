#include "Arduino.h"

void task1 ( void *param);
void task2 ( void *param);

TaskHandle_t TaskHandle_1 = NULL; // quản lý tác vụ
TaskHandle_t TaskHandle_2 = NULL;
QueueHandle_t Queue;              // quản lý hàng đợi


void setup() 
{
  Serial.begin(115200);
  // tạo ra 1 task và ghim nó vào core 1
  xTaskCreatePinnedToCore(task1, "task1", 1024, NULL, 1, &TaskHandle_1, 1); 
  xTaskCreatePinnedToCore(task2, "task2", 1024, NULL, 1, &TaskHandle_2, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void task1(void *p) 
{
  char myTxBuff[30];

  Queue = xQueueCreate(7, sizeof(myTxBuff));

  sprintf(myTxBuff, "Tek4VN");
  xQueueSend(Queue, (void*) myTxBuff, (TickType_t) 0);
  sprintf(myTxBuff, "https://tek4.vn/");
  xQueueSend(Queue, (void*) myTxBuff, (TickType_t) 0);
  sprintf(myTxBuff, "ESP32-FreeRTOS");
  xQueueSend(Queue, (void*) myTxBuff, (TickType_t) 0);
  sprintf(myTxBuff, "Xin chao cac ban");
  xQueueSend(Queue, (void*) myTxBuff, (TickType_t) 0);

  Serial.print("data waiting to be read: ");
  Serial.print(uxQueueMessagesWaiting(Queue)); // số dữ liệu chờ
  Serial.print("\n");
  Serial.print("available spaces: ");
  Serial.print(uxQueueSpacesAvailable(Queue)); // Kích thước còn chống
  Serial.print("\n");

  while (true) {}
}

void task2(void *p) 
{
  char myRxBuff[30];
  while (true) 
  {
    if (Queue != 0) 
    {
      if (xQueueReceive(Queue, (void*) myRxBuff, (TickType_t) 5)) 
      {
        Serial.print("data receive: ");
        Serial.print(myRxBuff);
        Serial.print("\n");
      }
    }
  }
}
