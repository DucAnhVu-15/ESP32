#include <Arduino.h>

int nTasks=4;
void genericTask(void * parameter);
/*
  Tạo một Semaphore đếm
  nTasks: số lượng task mà Semaphore sẽ được sử dụng để đồng bộ hóa
  0: giá trị ban đầu của Semaphore tức là khi Semaphore được khởi tạo, nó không có giá trị đếm
*/
SemaphoreHandle_t barrierSemaphore = xSemaphoreCreateCounting(nTasks, 0);

void setup() 
{
  Serial.begin(115200);
  Serial.println("Starting to launch tasks..");

  for(int i= 0; i< nTasks; i++)
  {
    xTaskCreatePinnedToCore(
                    genericTask,    /* Function to implement the task */
                    "genericTask",  /* Name of the task */
                    10000,          /* Stack size in words */
                    (void *)i,      /* Task input parameter, Truyền tham số đầu vào cho Task*/
                    0,              /* Priority of the task */
                    NULL,           /* Task handle. */
                    1);             /* Core where the task should run */
  }    

  for(int i= 0; i < nTasks; i++)
  {
    xSemaphoreTake(barrierSemaphore, portMAX_DELAY); // portMAX_DELAY: chờ vô thời hạn cho đến khi lấy được Semaphore
  }
  Serial.println("Tasks launched and semaphore passed...");
}

void loop() 
{
  // vTaskSuspend(NULL);
}

void genericTask(void * parameter)
{
  String taskMessage = "Task number:";
  taskMessage = taskMessage + ((int)parameter);
  Serial.println(taskMessage);
  // Tăng giá trị đếm của Semaphore bằng cách gọi hàm xSemaphoreGive()
  xSemaphoreGive(barrierSemaphore); 
  vTaskDelete(NULL);
}
