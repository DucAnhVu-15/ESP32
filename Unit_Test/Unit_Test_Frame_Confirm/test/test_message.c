// #ifdef TEST

#include "unity.h"

#include "message.h"
#include "convert.h"

void Print_Data_Message(uint8_t *arr, uint8_t length);

void test_create_message_set_port_A(void)
{
    uint8_t arr_frame_test[9] = {0x55, 0xAA, 0x01, 0x00, 0x05, 0x00, 0x01, 0xEA, 0x0E};
    uint8_t arr_frame_set_port[15];

    frame_Message_t frame_set_port_detect;

    uint16_t length = Message_Frame_Create_Set_Port(PORT_A, arr_frame_set_port);
    printf("/*-------------------------------------------------------------------------------------------------------*/");
    printf("\nStart test set port\n");
    printf("length_frame = %d\n", length);
    for (int i = 0; i < length; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(arr_frame_set_port[i], arr_frame_test[i]);

        printf("arr_frame_set_port[%d] = %x\n", i, arr_frame_set_port[i]);
    }

    /*---------------------------------------------------(END_CREAT_FRAME_SET PORT)----------------------------------------*/

    /*------------------------------------------------(START_DETECT_FRAME_SET PORT)----------------------------------------*/

    Message_Frame_Detect(arr_frame_set_port, &frame_set_port_detect);

    TEST_ASSERT_EQUAL_HEX16(frame_set_port_detect.StartFrame, START_BYTE);
    TEST_ASSERT_EQUAL_HEX16(frame_set_port_detect.TypeMessage, TYPE_MESSAGE_SET_PORT);
    TEST_ASSERT_EQUAL_HEX16(frame_set_port_detect.Length, LENGTH_MESSAGE_SET_PORT);
    TEST_ASSERT_EQUAL_HEX16(frame_set_port_detect.CheckFrame, 0x0EEA);

    /*---------------------------------------Get_Data------------------------------------------*/

    uint8_t get_port = Message_Get_Port(frame_set_port_detect);
    printf("get_port = %d\n", get_port);
    TEST_ASSERT_EQUAL_HEX8(get_port, PORT_A);
    printf("/************************************************************************************************************/\n");
}

void test_create_message_set_port_B(void)
{
    uint8_t arr_frame_test[9] = {0x55, 0xAA, 0x01, 0x00, 0x05, 0x00, 0x02, 0xAA, 0x0F};
    uint8_t arr_frame_set_port[15];

    frame_Message_t frame_set_port_detect;

    uint16_t length = Message_Frame_Create_Set_Port(PORT_B, arr_frame_set_port);
    printf("/*-------------------------------------------------------------------------------------------------------*/");
    printf("\nStart test set port\n");
    printf("length_frame = %d\n", length);
    for (int i = 0; i < length; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(arr_frame_set_port[i], arr_frame_test[i]);

        printf("arr_frame_set_port[%d] = %x\n", i, arr_frame_set_port[i]);
    }

    /*---------------------------------------------------(END_CREAT_FRAME_SET PORT)----------------------------------------*/

    /*------------------------------------------------(START_DETECT_FRAME_SET PORT)----------------------------------------*/

    Message_Frame_Detect(arr_frame_set_port, &frame_set_port_detect);

    TEST_ASSERT_EQUAL_HEX16(frame_set_port_detect.StartFrame, START_BYTE);
    TEST_ASSERT_EQUAL_HEX16(frame_set_port_detect.TypeMessage, TYPE_MESSAGE_SET_PORT);
    TEST_ASSERT_EQUAL_HEX16(frame_set_port_detect.Length, LENGTH_MESSAGE_SET_PORT);
    TEST_ASSERT_EQUAL_HEX16(frame_set_port_detect.CheckFrame, 0x0FAA);

    /*---------------------------------------Get_Data------------------------------------------*/

    uint8_t get_port = Message_Get_Port(frame_set_port_detect);
    printf("get_port = %d\n", get_port);
    TEST_ASSERT_EQUAL_HEX8(get_port, PORT_B);
    printf("/************************************************************************************************************/\n");
}

void test_Frame_ask_data(void)
{
    uint8_t count_test_arr = 0;
    frame_Message_t frame_ask_data, frame_ask_data_detect;

    uint8_t arr_frame_ask_data[50];

    uint8_t arr_frame_test[LENGTH_DEFAULT + LENGTH_MESSAGE_ASK_DATA] = {0x55, 0xAA, 0x02, 0x00, 0x06, 0x00, 0x02, 0x01, 0x4E, 0xC8};

    uint8_t length_frame = Message_Frame_Create_Ask(PORT_B, SENSOR_LUX, arr_frame_ask_data);

    printf("/*-------------------------------------------------------------------------------------------------------*/");
    printf("\nStart test ask data\n");
    printf("length_frame = %d\n", length_frame);

    for (count_test_arr = 0; count_test_arr < length_frame; count_test_arr++)
    {
        TEST_ASSERT_EQUAL_UINT8(arr_frame_test[count_test_arr], arr_frame_ask_data[count_test_arr]);
        printf("arr_frame_ask_data[%d] = %x\n", count_test_arr, arr_frame_ask_data[count_test_arr]);
    }

    /*---------------------------------------------------(END_CREAT_FRAME_ASK_DATA)----------------------------------------*/

    /*------------------------------------------------(START_DETECT_FRAME_ASK_DATA)----------------------------------------*/

    Message_Frame_Detect(arr_frame_ask_data, &frame_ask_data_detect);

    TEST_ASSERT_EQUAL_HEX16(frame_ask_data_detect.StartFrame, START_BYTE);
    TEST_ASSERT_EQUAL_HEX16(frame_ask_data_detect.TypeMessage, TYPE_MESSAGE_ASK_DATA);
    TEST_ASSERT_EQUAL_HEX16(frame_ask_data_detect.Length, LENGTH_MESSAGE_ASK_DATA);

    /*---------------------------------------Get_Data------------------------------------------*/
    uint8_t get_port = Message_Get_Port(frame_ask_data_detect);
    printf("get_port = %d\n", get_port);
    uint8_t get_type_sensor = Message_Get_Type_Sensor(frame_ask_data_detect);
    printf("get_type_sensor = %d\n", get_type_sensor);

    TEST_ASSERT_EQUAL_HEX8(get_port, PORT_B);
    TEST_ASSERT_EQUAL_HEX8(get_type_sensor, SENSOR_LUX);
    printf("/************************************************************************************************************/\n");
}

void test_Frame_Sensor_Confirm_Port(void)
{
    uint8_t count_test_arr = 0;
    frame_Message_t frame_sensor_confirm_port, frame_sensor_confirm_port_detect;

    uint8_t arr_frame_confirm_port[50];

    uint8_t arr_frame_test[LENGTH_DEFAULT + LENGTH_MESSAGE_CONFIRM] = {0x55, 0xAA, 0x03, 0x00, 0x06, 0x00, 0x02, 0x01, 0x4F, 0x19};

    uint8_t length_frame = Messagee_Frame_Create_Confirm(PORT_B, SENSOR_LUX, arr_frame_confirm_port);

    printf("/*-------------------------------------------------------------------------------------------------------*/");
    printf("\nStart test confirm\n");
    printf("length_frame = %d\n", length_frame);

    for (count_test_arr = 0; count_test_arr < length_frame; count_test_arr++)
    {
        TEST_ASSERT_EQUAL_UINT8(arr_frame_test[count_test_arr], arr_frame_confirm_port[count_test_arr]);
        printf("arr_frame_confirm_port[%d] = %x\n", count_test_arr, arr_frame_confirm_port[count_test_arr]);
    }
    /*---------------------------------------------------(END_CREAT_FRAME_CONFIRM)----------------------------------------*/

    /*------------------------------------------------(START_DETECT_FRAME_CONFIRM)----------------------------------------*/
    Message_Frame_Detect(arr_frame_confirm_port, &frame_sensor_confirm_port_detect);

    TEST_ASSERT_EQUAL_HEX16(frame_sensor_confirm_port_detect.StartFrame, START_BYTE);
    TEST_ASSERT_EQUAL_HEX16(frame_sensor_confirm_port_detect.TypeMessage, TYPE_MESSAGE_SENSOR_CONFIRM);
    TEST_ASSERT_EQUAL_HEX16(frame_sensor_confirm_port_detect.Length, LENGTH_MESSAGE_CONFIRM);

    uint8_t get_port = Message_Get_Port(frame_sensor_confirm_port_detect);
    printf("get_port = %d\n", get_port);
    uint8_t get_type_sensor = Message_Get_Type_Sensor(frame_sensor_confirm_port_detect);
    printf("get_type_sensor = %d\n", get_type_sensor);
    TEST_ASSERT_EQUAL_HEX8(get_port, PORT_B);
    TEST_ASSERT_EQUAL_HEX8(get_type_sensor, SENSOR_LUX);
    printf("/************************************************************************************************************/\n");
}

void test_Frame_Respond_Data_Lux(void)
{
    float float_test = 26.03;
    uint8_t count_test_arr = 0;
    frame_Message_t frame_respond_data, frame_respond_data_detect;

    uint8_t arr_frame_respond_data[50];

    uint8_t arr_frame_test[LENGTH_DEFAULT + LENGTH_MESSAGE_RESPOND_LUX] = {0x55, 0xAA, 0x04, 0x00, 0x0A, 0x00, 0x02, 0x01, 0x71, 0x3D, 0xD0, 0x41, 0x61, 0x9C};

    uint8_t length_frame = Message_Frame_Response_LUX(PORT_B, SENSOR_LUX, float_test, arr_frame_respond_data);

    printf("/*-------------------------------------------------------------------------------------------------------*/");
    printf("\nStart test respond data\n");
    printf("length_frame = %d\n", length_frame);

    for (count_test_arr = 0; count_test_arr < length_frame; count_test_arr++)
    {
        TEST_ASSERT_EQUAL_UINT8(arr_frame_test[count_test_arr], arr_frame_respond_data[count_test_arr]);
        printf("arr_frame_respond_data[%d] = %x\n", count_test_arr, arr_frame_respond_data[count_test_arr]);
    }
    /*---------------------------------------------------(END_CREAT_FRAME_RESPOND_DATA_LUX)----------------------------------------*/

    /*------------------------------------------------(START_DETECT_FRAME_RESPOND_DATA_LUX)----------------------------------------*/

    Message_Frame_Detect(arr_frame_respond_data, &frame_respond_data_detect);

    TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.StartFrame, START_BYTE);
    TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.TypeMessage, TYPE_MESSAGE_SENSOR_RESPOND_DATA);
    TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.Length, LENGTH_MESSAGE_RESPOND_LUX);
    TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.Data[0], 0x02);
    TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.Data[1], 0x01);
    TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.Data[2], 0x71);
    TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.Data[3], 0x3D);
    TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.Data[4], 0xD0);
    TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.Data[5], 0x41);

    /*---------------------------------------------------(END_DETECT_FRAME_RESPOND_DATA_LUX)----------------------------------------*/
    uint8_t get_port = Message_Get_Port(frame_respond_data_detect);
    printf("get_port = %d\n", get_port);
    uint8_t get_type_sensor = Message_Get_Type_Sensor(frame_respond_data_detect);
    printf("get_type_sensor = %d\n", get_type_sensor);
    TEST_ASSERT_EQUAL_HEX8(get_port, PORT_B);
    TEST_ASSERT_EQUAL_HEX8(get_type_sensor, SENSOR_LUX);
    float get_data = Message_Get_Data_Sensor_Lux(frame_respond_data_detect);
    printf("get_data = %.2f\n", get_data);
    TEST_ASSERT_EQUAL_FLOAT(float_test, get_data);
    printf("/************************************************************************************************************/\n");
}

// void test_Frame_Respond_Data_NTC(void)
// {
//     float float_test = 31.58;
//     uint8_t count_test_arr = 0;
//     frame_Message_t frame_respond_data, frame_respond_data_detect;

//     uint8_t arr_frame_respond_data[50];

//     uint8_t arr_frame_test[LENGTH_DEFAULT + LENGTH_MESSAGE_RESPOND_NTC] = {0x55, 0xAA, 0x04, 0x00, 0x0A, 0x00, 0x02, 0x03, 0xD7, 0xA3, 0xFC, 0x41, 0x47, 0xFA};

//     uint8_t length_frame = Message_Frame_Response_NTC(PORT_B, SENSOR_NTC, float_test, arr_frame_respond_data);

//     printf("/*-------------------------------------------------------------------------------------------------------*/");
//     printf("\nStart test respond data\n");
//     printf("length_frame = %d\n", length_frame);

//     for (count_test_arr = 0; count_test_arr < length_frame; count_test_arr++)
//     {
//         TEST_ASSERT_EQUAL_UINT8(arr_frame_test[count_test_arr], arr_frame_respond_data[count_test_arr]);
//         printf("arr_frame_respond_data[%d] = %x\n", count_test_arr, arr_frame_respond_data[count_test_arr]);
//     }
//     /*---------------------------------------------------(END_CREAT_FRAME_RESPOND_DATA_NTC)----------------------------------------*/

//     /*------------------------------------------------(START_DETECT_FRAME_RESPOND_DATA_NTC)----------------------------------------*/

//     Message_Frame_Detect(arr_frame_respond_data, &frame_respond_data_detect);
//     TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.StartFrame, START_BYTE);
//     TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.TypeMessage, TYPE_MESSAGE_SENSOR_RESPOND_DATA);
//     TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.Length, LENGTH_MESSAGE_RESPOND_NTC);
//     TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.Data[0], 0x02);
//     TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.Data[1], 0x03);
//     TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.Data[2], 0xD7);
//     TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.Data[3], 0xA3);
//     TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.Data[4], 0xFC);
//     TEST_ASSERT_EQUAL_HEX16(frame_respond_data_detect.Data[5], 0x41);

//     /*---------------------------------------------------(END_DETECT_FRAME_RESPOND_DATA_NTC)----------------------------------------*/
//     uint8_t get_port = Message_Get_Port(frame_respond_data_detect);
//     printf("get_port = %d\n", get_port);
//     uint8_t get_type_sensor = Message_Get_Type_Sensor(frame_respond_data_detect);
//     printf("get_type_sensor = %d\n", get_type_sensor);
//     float get_data = Message_Get_Data_Sensor_NTC(frame_respond_data_detect);
//     printf("get_data = %.2f\n", get_data);
//     TEST_ASSERT_EQUAL_FLOAT(float_test, get_data);
//     printf("/************************************************************************************************************/\n");
//     printf("/************************************************************************************************************/\n");
// }

void test_Frame_Respond_Data_Res()
{
    uint16_t value_test = 100;
    uint8_t count_test_arr = 0;
    frame_Message_t frame_respond_data, frame_respond_data_detect;
    uint8_t arr_frame_respond_data[50];
    uint8_t arr_frame_test[LENGTH_DEFAULT + LENGTH_MESSAGE_RESPOND_RES] = {0x55, 0xAA, 0x04, 0x00, 0x0A, 0x00, 0x02, 0x05, 0x64, 0x04, 0x00, 0x64};
    uint8_t length_frame = Message_Create_Frame_Respond_RES(value_test, arr_frame_respond_data);
    printf("/*-------------------------------------------------------------------------------------------------------*/");
    printf("\nStart test respond data\n");
    printf("length_frame = %d\n", length_frame);

    for (count_test_arr = 0; count_test_arr < length_frame; count_test_arr++)
    {
        // TEST_ASSERT_EQUAL_UINT8(arr_frame_test[count_test_arr], arr_frame_respond_data[count_test_arr]);
        printf("arr_frame_respond_data[%d] = %x\n", count_test_arr, arr_frame_respond_data[count_test_arr]);
    }
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
// #endif // TEST
