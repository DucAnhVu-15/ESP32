#include <Arduino.h>

QueueHandle_t xMailBox;
TaskHandle_t TaskHandle_1; // handler for Task 1
TaskHandle_t TaskHandle_2; // handler for Task 2

void vUpdateMailBox(void *parameters);
void vReadMailBox(void *parameters);

void setup()
{
  Serial.begin(112500);
  // Tạo ra một MailBox với một vị trí lưu trữ và kích thước mỗi ptu là kích thước của uint32_t
  xMailBox = xQueueCreate(1, sizeof(uint32_t));
  // Sau khi tác vụ được tạo, xử lý tác vụ sẽ được lưu trữ trong tệp TaskHandle_1.
  xTaskCreate(vUpdateMailBox, (char *) "Sender", 10000, NULL, 1, &TaskHandle_1);
  xTaskCreate(vReadMailBox, (char *) "Receiver", 10000, NULL, 1, &TaskHandle_2);
}

void loop()
{

}

void vUpdateMailBox(void *parameters)
{
  uint32_t ulNewValue = 1;
  while(1)
  {
    // Được sử dụng để ghi đè giá trị ulNewValue vào xMailBox
    xQueueOverwrite(xMailBox, &ulNewValue);
    Serial.println("Ghi giá trị vào MailBox");
    ulNewValue++;
    if(ulNewValue > 100)
    {
      ulNewValue = 0;
    }

    vTaskDelay(1000);
  }
}

void vReadMailBox(void *parameters)
{
  uint32_t value_receive;
  while(1)
  {
    /*
      Giá trị được lưu trữ trong xMailBox được sao chép vào value_receive mà không xóa đi
      và đợi vô thời hạn cho đến khi giá trị được lưu vào trong MailBox
    */
    xQueuePeek(xMailBox, &value_receive, portMAX_DELAY);
    Serial.print("Giá trị đọc được từ MailBox = ");
    Serial.println(value_receive);
    
    vTaskDelay(950);
  }
}
