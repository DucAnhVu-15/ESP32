#include "lib_sys.h"


QueueHandle_t xQueue;
SemaphoreHandle_t xMutex;
EventGroupHandle_t xEvent;


void SYS_Setup(void)
{
    Serial.begin(115200);
    LED_Init();
    BUTTON_Init();

    xMutex = xSemaphoreCreateMutex();
    xEvent = xEventGroupCreate();
    
    xTaskCreatePinnedToCore(TASK_Button, (char *) "Task Button", 1024, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(TASK_LedRed, (char *) "Task LedRed", 1024, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(TASK_LedGreen, (char *) "Task LedGreen", 1024, NULL, 1, NULL, 1);
}

void SYS_Run(void)
{
    vTaskDelete(NULL);
}

void TASK_LedRed(void *parameters)
{
    uint32_t event_flag_1 = 0;
    while(1)
    {
        event_flag_1 = xEventGroupWaitBits(xEvent, 1, pdTRUE, pdFALSE, portMAX_DELAY);
        if(event_flag_1 == 0x01)
        {
            xSemaphoreTake(xMutex, portMAX_DELAY);
            Serial.println("Led Red");
            LED_RED();
            xSemaphoreGive(xMutex);
        }
    }
}

void TASK_LedGreen(void *parameters)
{
    uint32_t event_flag_2 = 0;
    while(1)
    {
        event_flag_2 = xEventGroupWaitBits(xEvent, 2, pdTRUE, pdFALSE, portMAX_DELAY);
        if(event_flag_2 == 0x02)
        {
            xSemaphoreTake(xMutex, portMAX_DELAY);
            Serial.println("Led Green");
            LED_GREEN();
            xSemaphoreGive(xMutex);
        }
    }
}

void TASK_Button(void *parameters)
{
    uint32_t count_prees = 0;
    
    while(1)
    {
        BUTTON_Read();

        if(button_flag == 1)
        {
            Serial.println("Button");
            count_prees++;
            if(count_prees < 4)
            {
                xEventGroupSetBits(xEvent, 1);
            }

            if(count_prees >= 4)
            {
                xEventGroupSetBits(xEvent, 2);
                count_prees = 2;
            }
            button_flag = 0;
        }
    }
}
