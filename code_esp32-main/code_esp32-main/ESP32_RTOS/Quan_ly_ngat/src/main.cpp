#include <Arduino.h>

SemaphoreHandle_t interruptSemaphore;


void interruptHandler();
void TaskLedon(void *pvParameters);
void TaskLedoff(void *pvParameters);

void setup() 
{
  Serial.begin(115200); // Enable serial communication library.

  xTaskCreate(TaskLedon, // Task function
              "Ledon", // Task name
              1024, // Stack size 
              NULL, 
              0 ,// Priority
              NULL );

   xTaskCreate(TaskLedoff, // Task function
              "Ledoff", // Task name
              1024, // Stack size 
              NULL, 
              0, // Priority
              NULL );

  interruptSemaphore = xSemaphoreCreateBinary(); // Semaphore nhị phân 0 or 1

  if (interruptSemaphore != NULL) 
  {
    attachInterrupt(2, interruptHandler, HIGH);
  }  
}

void loop() {}

void interruptHandler() 
{ 
  Serial.println("Semaphore is given");
  BaseType_t  xHigherPriorityTaskWoken  pdFALSE; // Khởi tạo giá trị bool
  xSemaphoreGiveFromISR(interruptSemaphore, &xHigherPriorityTaskWoken);
}

void TaskLedon(void *pvParameters)
{
  (void) pvParameters;

  while(1) 
  {
    if (xSemaphoreTake(interruptSemaphore, portMAX_DELAY) == pdPASS) 
    {
      Serial.println("TaskLedon Received Semaphore");
      delay(100);
    }
  }
}

void TaskLedoff(void *pvParameters)
{
  (void) pvParameters;
  while(1)
  {
    if (xSemaphoreTake(interruptSemaphore, portMAX_DELAY) == pdPASS)
    {
      Serial.println("TaskLedoff Received Semaphore");
      delay(100);
    }
    
  }
}