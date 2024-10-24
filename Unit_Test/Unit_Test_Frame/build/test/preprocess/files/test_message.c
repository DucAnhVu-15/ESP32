#include "src/convert.h"
#include "src/message.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"






void Print_Data_Message(uint8_t *arr, uint8_t length);

void test_Frame_Sensor_Confirm_Port(void)

{

    uint8_t count_test_Frame_Sensor_Confirm_Port = 0;

    frame_Sensor_t frame_sensor_confirm_port;



    uint8_t arr_frame_confirm_port[50];



    uint8_t arr_frame_test_confirm_port[0x03 + 0x05 + 2] = {0x55, 0xAA, 0x03, 0x00, 0x05, 0x00, 0x01, 0x02, 0x0F, 0xAC};

    printf("/*-------------------------------------------------------------------------------------------------------\n*/");



    frame_sensor_confirm_port.Data[0] = SENSOR_LUX;;

    frame_sensor_confirm_port.Data[1] = PORT_NUMBER_2;



    uint8_t length_frame_confirm_port = Message_Create_Frame_Confirm(frame_sensor_confirm_port, arr_frame_confirm_port);



    printf("/*-------------------------------------------------------------------------------------------------------*/");

    printf("\nStart test\n");

    printf("/*-------------------------------------------------------------------------------------------------------*/\n");

    printf("length_frame_confirm_port = %d\n", length_frame_confirm_port);



    Print_Data_Message(arr_frame_confirm_port, length_frame_confirm_port);



    for (count_test_Frame_Sensor_Confirm_Port = 0; count_test_Frame_Sensor_Confirm_Port < length_frame_confirm_port; count_test_Frame_Sensor_Confirm_Port++)

    {



        printf("arr_frame_confirm_port[%d] = %x\n", count_test_Frame_Sensor_Confirm_Port, arr_frame_confirm_port[count_test_Frame_Sensor_Confirm_Port]);

        printf("arr_frame_test_confirm_port[%d] = %x\n", count_test_Frame_Sensor_Confirm_Port, arr_frame_test_confirm_port[count_test_Frame_Sensor_Confirm_Port]);

    }



    printf("Test passed\n");

    printf("/*-------------------------------------------------------------------------------------------------------*/");

}

void Print_Data_Message(uint8_t *arr, uint8_t length)

{

    for (uint8_t i = 0; i < length; i++)

    {

        if (arr[i] <= 0x0F)

        {

            printf("0%x ", arr[i]);

        }

        else

        {

            printf("%x ", arr[i]);

        }

    }

    printf("\n");

}
