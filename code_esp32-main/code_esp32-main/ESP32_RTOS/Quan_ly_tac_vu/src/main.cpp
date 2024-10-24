#include <Arduino.h>

#define LED_1 22
#define LED_2 23

int count_1 = 0, count_2 = 0;
void Task_1(void *parameters);
void Task_2(void *parameters);

void setup() {
  Serial.begin(112500);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  // xTaskCreate(function_name, task_name, stack_size, task_parameters, task_priority, task_handle)
  xTaskCreate(Task_1, (char *) "Task 1", 1000, NULL, 1, NULL); 
  xTaskCreate(Task_2, (char *) "Task 2", 1000, NULL, 1, NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void Task_1(void *parameters)
{
  while(1)
  {
    digitalWrite(LED_1, LOW);
    vTaskDelay(500/portTICK_PERIOD_MS);
    digitalWrite(LED_1, HIGH);
    vTaskDelay(500/portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}

void Task_2(void *parameters)
{
  while(1)
  {
    digitalWrite(LED_2, LOW);
    vTaskDelay(3000/portTICK_PERIOD_MS);
    digitalWrite(LED_2, HIGH);
    vTaskDelay(3000/portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}
