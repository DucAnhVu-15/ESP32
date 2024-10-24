// #ifdef TEST

#include "unity.h"

#include "message.h"
#include "convert.h"
void Print_Data_Message(uint8_t *arr, uint8_t length);

void test_Frame_Message_Set_Port(void)
{
    uint8_t count_test_Frame_Message_Set_Port = 0;
    frame_Master_t frame_master_set_port;

    uint8_t arr_frame_set_port[50];

    // Assuming these values are defined elsewhere
    uint8_t arr_frame_test_set_port[LENGTH_DEFAULT + LENGTH_MESSAGE_SET_PORT + 2] = {0x55, 0xAA, 0x01, 0x00, 0x03, 0x00, 0x02, 0xFB, 0xCF};   

    // Setting up frame_master_set_port
    frame_master_set_port.StartFrame = 0xAA55;  // 2 byte
    frame_master_set_port.TypeMessage = TYPE_MESSAGE_SET_PORT;   // 1 byte
    frame_master_set_port.Data[0] = PORT_NUMBER_2;       // 1 byte    

    // Display frame_master_set_port details
    printf("/*-------------------------------------------------------------------------------------------------------\n*/");
    printf("frame_master_set_port.StartFrame = %x\n", frame_master_set_port.StartFrame);
    printf("frame_master_set_port.TypeMessage = %x\n", frame_master_set_port.TypeMessage);
    printf("/*-------------------------------------------------------------------------------------------------------\n*/");

    // Create the frame and get its length
    uint8_t length_frame_set_port = Message_Create_Frame_Master(frame_master_set_port, arr_frame_set_port);

    // Display length and frame contents
    printf("\nStart test\n");
    printf("/*-------------------------------------------------------------------------------------------------------*/\n");
    printf("length_frame = %d\n", length_frame_set_port);
    Print_Data_Message(arr_frame_set_port, length_frame_set_port);

    for (int i = 0; i < length_frame_set_port; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(arr_frame_test_set_port[i], arr_frame_set_port[i]);
        printf("arr_frame[%d] = %x\n", i, arr_frame_set_port[i]);
        printf("arr_frame_test[%d] = %x\n", i, arr_frame_test_set_port[i]);
        
    }

    printf("Test passed\n");
    printf("/*-------------------------------------------------------------------------------------------------------*/\n");
}



void test_Frame_Message_Ask_Data(void)
{
    uint8_t count_test_Frame_Message_Ask_Data = 0;
    frame_Master_t frame_master_ask_data;

    uint8_t arr_frame_ask_data[50];

    uint8_t arr_frame_test_ask_data[LENGTH_DEFAULT + LENGTH_MESSAGE_ASK_DATA + 2] = {0x55, 0xAA, 0x02, 0x04, 0x00, 0x01, 0x04, 0x0F, 0x81};
    printf("/*-------------------------------------------------------------------------------------------------------\n*/");

    frame_master_ask_data.StartFrame = START_BYTE;             // Assuming START_BYTE is defined elsewhere
    frame_master_ask_data.TypeMessage = TYPE_MESSAGE_ASK_DATA;  // Assuming TYPE_MASTER_START is defined elsewhere
    frame_master_ask_data.Data[0] = 0x01;
    frame_master_ask_data.Data[1] = 0x02;

    uint8_t length_frame_ask_data = Message_Create_Frame_Master(frame_master_ask_data, arr_frame_ask_data);

    printf("/*-------------------------------------------------------------------------------------------------------*/");
    printf("\nStart test\n");
    printf("/*-------------------------------------------------------------------------------------------------------*/\n");
    printf("length_frame = %d\n", length_frame_ask_data);
    
    Print_Data_Message(arr_frame_ask_data, length_frame_ask_data);

    for (count_test_Frame_Message_Ask_Data = 0; count_test_Frame_Message_Ask_Data < length_frame_ask_data; count_test_Frame_Message_Ask_Data++)
    {
        TEST_ASSERT_EQUAL_UINT8(arr_frame_test_ask_data[count_test_Frame_Message_Ask_Data], arr_frame_ask_data[count_test_Frame_Message_Ask_Data]);
        printf("arr_frame_ask_data[%d] = %x\n", count_test_Frame_Message_Ask_Data, arr_frame_ask_data[count_test_Frame_Message_Ask_Data]);
        printf("arr_frame_test_ask_data[%d] = %x\n", count_test_Frame_Message_Ask_Data, arr_frame_test_ask_data[count_test_Frame_Message_Ask_Data]);
    }

    printf("Test passed\n");
    printf("/*-------------------------------------------------------------------------------------------------------*/\n");
}

// void test_Frame_Sensor_Confirm_Port(void)
// {
//     uint8_t count_test_Frame_Sensor_Confirm_Port = 0;
//     frame_Sensor_t frame_sensor_confirm_port;

//     uint8_t arr_frame_confirm_port[50];

//     uint8_t arr_frame_test_confirm_port[LENGTH_DEFAULT + LENGTH_MESSAGE_SENSOR_CONFIRM + 2] = {0x55, 0xAA, 0x03, 0x00, 0x05, 0x00, 0x01, 0x02, 0x0F, 0xAC};
//     printf("/*-------------------------------------------------------------------------------------------------------\n*/");

//     frame_sensor_confirm_port.Data[0] = SENSOR_LUX;;
//     frame_sensor_confirm_port.Data[1] = PORT_NUMBER_2;

//     uint8_t length_frame_confirm_port = Message_Create_Frame_Confirm(frame_sensor_confirm_port, arr_frame_confirm_port);

//     printf("/*-------------------------------------------------------------------------------------------------------*/");
//     printf("\nStart test\n");
//     printf("/*-------------------------------------------------------------------------------------------------------*/\n");
//     printf("length_frame_confirm_port = %d\n", length_frame_confirm_port);

//     Print_Data_Message(arr_frame_confirm_port, length_frame_confirm_port);

//     for (count_test_Frame_Sensor_Confirm_Port = 0; count_test_Frame_Sensor_Confirm_Port < length_frame_confirm_port; count_test_Frame_Sensor_Confirm_Port++)
//     {
//         // TEST_ASSERT_EQUAL_UINT8(arr_frame_test_confirm_port[count_test_Frame_Sensor_Confirm_Port], arr_frame_confirm_port[count_test_Frame_Sensor_Confirm_Port]);
//         printf("arr_frame_confirm_port[%d] = %x\n", count_test_Frame_Sensor_Confirm_Port, arr_frame_confirm_port[count_test_Frame_Sensor_Confirm_Port]);
//         printf("arr_frame_test_confirm_port[%d] = %x\n", count_test_Frame_Sensor_Confirm_Port, arr_frame_test_confirm_port[count_test_Frame_Sensor_Confirm_Port]);
//     }

//     printf("Test passed\n");
//     printf("/*-------------------------------------------------------------------------------------------------------*/");
// }

// void test_Frame_Sensor_Respond_Data(void)
// {
//     uint8_t count_test_Frame_Sensor_Respond_Data = 0;
//     frame_Sensor_t frame_sensor_respond_data;

//     uint8_t arr_frame_respond_data[50];

//     uint8_t arr_frame_test_respond_data[LENGTH_DEFAULT + LENGTH_MESSAGE_SENSOR_RESPOND_DATA + 2] = {0x55, 0xAA, 0x04, 0x00, 0x06, 0x00, 0x01, 0x02, 0x03, 0x04, 0x45, 0x6B};
//     printf("/*-------------------------------------------------------------------------------------------------------\n*/");

//     frame_sensor_respond_data.StartFrame = START_BYTE;                    // Assuming START_BYTE is defined elsewhere
//     frame_sensor_respond_data.TypeMessage = TYPE_MESSAGE_SENSOR_SENDDATA; // Assuming TYPE_MASTER_START is defined elsewhere
//     frame_sensor_respond_data.LengthData = LENGTH_SENSOR_RESPOND_DATA;    // Assuming LENGTH_MASTER_SET_PORT is defined elsewhere
//     frame_sensor_respond_data.Data[0] = 0x01;
//     frame_sensor_respond_data.Data[1] = 0x02;
//     frame_sensor_respond_data.Data[2] = 0x03;
//     frame_sensor_respond_data.Data[3] = 0x04;
//     frame_sensor_respond_data.CheckFrame = CheckSum((uint8_t *)&frame_sensor_respond_data, (LENGTH_DEFAULT + frame_sensor_respond_data.LengthData));

//     printf("frame_sensor_respond_data.checkFrame = %x\n", frame_sensor_respond_data.CheckFrame);

//     uint8_t length_frame_respond_data = Message_Create_Frame_Slave(frame_sensor_respond_data, arr_frame_respond_data);

//     printf("/*-------------------------------------------------------------------------------------------------------*/");
//     printf("\nStart test\n");
//     printf("/*-------------------------------------------------------------------------------------------------------*/\n");
//     printf("length_frame_respond_data = %d\n", length_frame_respond_data);

//     for (count_test_Frame_Sensor_Respond_Data = 0; count_test_Frame_Sensor_Respond_Data < length_frame_respond_data; count_test_Frame_Sensor_Respond_Data++)
//     {
//         TEST_ASSERT_EQUAL_UINT8(arr_frame_test_respond_data[count_test_Frame_Sensor_Respond_Data], arr_frame_respond_data[count_test_Frame_Sensor_Respond_Data]);
//         printf("arr_frame_respond_data[%d] = %x\n", count_test_Frame_Sensor_Respond_Data, arr_frame_respond_data[count_test_Frame_Sensor_Respond_Data]);
//         printf("arr_frame_test_respond_data[%d] = %x\n", count_test_Frame_Sensor_Respond_Data, arr_frame_test_respond_data[count_test_Frame_Sensor_Respond_Data]);
//     }
//     printf("Test passed\n");
//     printf("/*-------------------------------------------------------------------------------------------------------*/");
// }

// #endif // TEST

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