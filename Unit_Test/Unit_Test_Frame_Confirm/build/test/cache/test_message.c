#include "src/convert.h"
#include "src/message.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








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

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((arr_frame_set_port[i])), (UNITY_INT)(UNITY_UINT8 )((arr_frame_test[i])), (

       ((void *)0)

       ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_UINT8);



        printf("arr_frame_set_port[%d] = %x\n", i, arr_frame_set_port[i]);

    }











    Message_Frame_Detect(arr_frame_set_port, &frame_set_port_detect);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_set_port_detect.StartFrame)), (UNITY_INT)(UNITY_INT16)((0XAA55)), (

   ((void *)0)

   ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_set_port_detect.TypeMessage)), (UNITY_INT)(UNITY_INT16)((TYPE_MESSAGE_SET_PORT)), (

   ((void *)0)

   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_set_port_detect.Length)), (UNITY_INT)(UNITY_INT16)((0x05)), (

   ((void *)0)

   ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_set_port_detect.CheckFrame)), (UNITY_INT)(UNITY_INT16)((0x0EEA)), (

   ((void *)0)

   ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_HEX16);







    uint8_t get_port = Message_Get_Port(frame_set_port_detect);

    printf("get_port = %d\n", get_port);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((get_port)), (UNITY_INT)(UNITY_INT8 )((PORT_A)), (

   ((void *)0)

   ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_HEX8);

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

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((arr_frame_set_port[i])), (UNITY_INT)(UNITY_UINT8 )((arr_frame_test[i])), (

       ((void *)0)

       ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_UINT8);



        printf("arr_frame_set_port[%d] = %x\n", i, arr_frame_set_port[i]);

    }











    Message_Frame_Detect(arr_frame_set_port, &frame_set_port_detect);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_set_port_detect.StartFrame)), (UNITY_INT)(UNITY_INT16)((0XAA55)), (

   ((void *)0)

   ), (UNITY_UINT)(71), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_set_port_detect.TypeMessage)), (UNITY_INT)(UNITY_INT16)((TYPE_MESSAGE_SET_PORT)), (

   ((void *)0)

   ), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_set_port_detect.Length)), (UNITY_INT)(UNITY_INT16)((0x05)), (

   ((void *)0)

   ), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_set_port_detect.CheckFrame)), (UNITY_INT)(UNITY_INT16)((0x0FAA)), (

   ((void *)0)

   ), (UNITY_UINT)(74), UNITY_DISPLAY_STYLE_HEX16);







    uint8_t get_port = Message_Get_Port(frame_set_port_detect);

    printf("get_port = %d\n", get_port);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((get_port)), (UNITY_INT)(UNITY_INT8 )((PORT_B)), (

   ((void *)0)

   ), (UNITY_UINT)(80), UNITY_DISPLAY_STYLE_HEX8);

    printf("/************************************************************************************************************/\n");

}



void test_Frame_ask_data(void)

{

    uint8_t count_test_arr = 0;

    frame_Message_t frame_ask_data, frame_ask_data_detect;



    uint8_t arr_frame_ask_data[50];



    uint8_t arr_frame_test[0x04 + 0x06] = {0x55, 0xAA, 0x02, 0x00, 0x06, 0x00, 0x02, 0x01, 0x4E, 0xC8};



    uint8_t length_frame = Message_Frame_Create_Ask(PORT_B, SENSOR_LUX, arr_frame_ask_data);



    printf("/*-------------------------------------------------------------------------------------------------------*/");

    printf("\nStart test ask data\n");

    printf("length_frame = %d\n", length_frame);



    for (count_test_arr = 0; count_test_arr < length_frame; count_test_arr++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((arr_frame_test[count_test_arr])), (UNITY_INT)(UNITY_UINT8 )((arr_frame_ask_data[count_test_arr])), (

       ((void *)0)

       ), (UNITY_UINT)(101), UNITY_DISPLAY_STYLE_UINT8);

        printf("arr_frame_ask_data[%d] = %x\n", count_test_arr, arr_frame_ask_data[count_test_arr]);

    }











    Message_Frame_Detect(arr_frame_ask_data, &frame_ask_data_detect);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_ask_data_detect.StartFrame)), (UNITY_INT)(UNITY_INT16)((0XAA55)), (

   ((void *)0)

   ), (UNITY_UINT)(111), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_ask_data_detect.TypeMessage)), (UNITY_INT)(UNITY_INT16)((TYPE_MESSAGE_ASK_DATA)), (

   ((void *)0)

   ), (UNITY_UINT)(112), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_ask_data_detect.Length)), (UNITY_INT)(UNITY_INT16)((0x06)), (

   ((void *)0)

   ), (UNITY_UINT)(113), UNITY_DISPLAY_STYLE_HEX16);





    uint8_t get_port = Message_Get_Port(frame_ask_data_detect);

    printf("get_port = %d\n", get_port);

    uint8_t get_type_sensor = Message_Get_Type_Sensor(frame_ask_data_detect);

    printf("get_type_sensor = %d\n", get_type_sensor);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((get_port)), (UNITY_INT)(UNITY_INT8 )((PORT_B)), (

   ((void *)0)

   ), (UNITY_UINT)(121), UNITY_DISPLAY_STYLE_HEX8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((get_type_sensor)), (UNITY_INT)(UNITY_INT8 )((SENSOR_LUX)), (

   ((void *)0)

   ), (UNITY_UINT)(122), UNITY_DISPLAY_STYLE_HEX8);

    printf("/************************************************************************************************************/\n");

}



void test_Frame_Sensor_Confirm_Port(void)

{

    uint8_t count_test_arr = 0;

    frame_Message_t frame_sensor_confirm_port, frame_sensor_confirm_port_detect;



    uint8_t arr_frame_confirm_port[50];



    uint8_t arr_frame_test[0x04 + 0x06] = {0x55, 0xAA, 0x03, 0x00, 0x06, 0x00, 0x02, 0x01, 0x4F, 0x19};



    uint8_t length_frame = Messagee_Frame_Create_Confirm(PORT_B, SENSOR_LUX, arr_frame_confirm_port);



    printf("/*-------------------------------------------------------------------------------------------------------*/");

    printf("\nStart test confirm\n");

    printf("length_frame = %d\n", length_frame);



    for (count_test_arr = 0; count_test_arr < length_frame; count_test_arr++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((arr_frame_test[count_test_arr])), (UNITY_INT)(UNITY_UINT8 )((arr_frame_confirm_port[count_test_arr])), (

       ((void *)0)

       ), (UNITY_UINT)(143), UNITY_DISPLAY_STYLE_UINT8);

        printf("arr_frame_confirm_port[%d] = %x\n", count_test_arr, arr_frame_confirm_port[count_test_arr]);

    }







    Message_Frame_Detect(arr_frame_confirm_port, &frame_sensor_confirm_port_detect);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_sensor_confirm_port_detect.StartFrame)), (UNITY_INT)(UNITY_INT16)((0XAA55)), (

   ((void *)0)

   ), (UNITY_UINT)(151), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_sensor_confirm_port_detect.TypeMessage)), (UNITY_INT)(UNITY_INT16)((TYPE_MESSAGE_SENSOR_CONFIRM)), (

   ((void *)0)

   ), (UNITY_UINT)(152), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_sensor_confirm_port_detect.Length)), (UNITY_INT)(UNITY_INT16)((0x06)), (

   ((void *)0)

   ), (UNITY_UINT)(153), UNITY_DISPLAY_STYLE_HEX16);



    uint8_t get_port = Message_Get_Port(frame_sensor_confirm_port_detect);

    printf("get_port = %d\n", get_port);

    uint8_t get_type_sensor = Message_Get_Type_Sensor(frame_sensor_confirm_port_detect);

    printf("get_type_sensor = %d\n", get_type_sensor);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((get_port)), (UNITY_INT)(UNITY_INT8 )((PORT_B)), (

   ((void *)0)

   ), (UNITY_UINT)(159), UNITY_DISPLAY_STYLE_HEX8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((get_type_sensor)), (UNITY_INT)(UNITY_INT8 )((SENSOR_LUX)), (

   ((void *)0)

   ), (UNITY_UINT)(160), UNITY_DISPLAY_STYLE_HEX8);

    printf("/************************************************************************************************************/\n");

}



void test_Frame_Respond_Data_Lux(void)

{

    float float_test = 26.03;

    uint8_t count_test_arr = 0;

    frame_Message_t frame_respond_data, frame_respond_data_detect;



    uint8_t arr_frame_respond_data[50];



    uint8_t arr_frame_test[0x04 + 10] = {0x55, 0xAA, 0x04, 0x00, 0x0A, 0x00, 0x02, 0x01, 0x71, 0x3D, 0xD0, 0x41, 0x61, 0x9C};



    uint8_t length_frame = Message_Frame_Response_LUX(PORT_B, SENSOR_LUX, float_test, arr_frame_respond_data);



    printf("/*-------------------------------------------------------------------------------------------------------*/");

    printf("\nStart test respond data\n");

    printf("length_frame = %d\n", length_frame);



    for (count_test_arr = 0; count_test_arr < length_frame; count_test_arr++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((arr_frame_test[count_test_arr])), (UNITY_INT)(UNITY_UINT8 )((arr_frame_respond_data[count_test_arr])), (

       ((void *)0)

       ), (UNITY_UINT)(182), UNITY_DISPLAY_STYLE_UINT8);

        printf("arr_frame_respond_data[%d] = %x\n", count_test_arr, arr_frame_respond_data[count_test_arr]);

    }









    Message_Frame_Detect(arr_frame_respond_data, &frame_respond_data_detect);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_respond_data_detect.StartFrame)), (UNITY_INT)(UNITY_INT16)((0XAA55)), (

   ((void *)0)

   ), (UNITY_UINT)(191), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_respond_data_detect.TypeMessage)), (UNITY_INT)(UNITY_INT16)((TYPE_MESSAGE_SENSOR_RESPOND_DATA)), (

   ((void *)0)

   ), (UNITY_UINT)(192), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_respond_data_detect.Length)), (UNITY_INT)(UNITY_INT16)((10)), (

   ((void *)0)

   ), (UNITY_UINT)(193), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_respond_data_detect.Data[0])), (UNITY_INT)(UNITY_INT16)((0x02)), (

   ((void *)0)

   ), (UNITY_UINT)(194), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_respond_data_detect.Data[1])), (UNITY_INT)(UNITY_INT16)((0x01)), (

   ((void *)0)

   ), (UNITY_UINT)(195), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_respond_data_detect.Data[2])), (UNITY_INT)(UNITY_INT16)((0x71)), (

   ((void *)0)

   ), (UNITY_UINT)(196), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_respond_data_detect.Data[3])), (UNITY_INT)(UNITY_INT16)((0x3D)), (

   ((void *)0)

   ), (UNITY_UINT)(197), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_respond_data_detect.Data[4])), (UNITY_INT)(UNITY_INT16)((0xD0)), (

   ((void *)0)

   ), (UNITY_UINT)(198), UNITY_DISPLAY_STYLE_HEX16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((frame_respond_data_detect.Data[5])), (UNITY_INT)(UNITY_INT16)((0x41)), (

   ((void *)0)

   ), (UNITY_UINT)(199), UNITY_DISPLAY_STYLE_HEX16);





    uint8_t get_port = Message_Get_Port(frame_respond_data_detect);

    printf("get_port = %d\n", get_port);

    uint8_t get_type_sensor = Message_Get_Type_Sensor(frame_respond_data_detect);

    printf("get_type_sensor = %d\n", get_type_sensor);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((get_port)), (UNITY_INT)(UNITY_INT8 )((PORT_B)), (

   ((void *)0)

   ), (UNITY_UINT)(206), UNITY_DISPLAY_STYLE_HEX8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((get_type_sensor)), (UNITY_INT)(UNITY_INT8 )((SENSOR_LUX)), (

   ((void *)0)

   ), (UNITY_UINT)(207), UNITY_DISPLAY_STYLE_HEX8);

    float get_data = Message_Get_Data_Sensor_Lux(frame_respond_data_detect);

    printf("get_data = %.2f\n", get_data);

    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((float_test)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((float_test))), (UNITY_FLOAT)((UNITY_FLOAT)((get_data))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(210)));

    printf("/************************************************************************************************************/\n");

}

void test_Frame_Respond_Data_Res()

{

    uint16_t value_test = 100;

    uint8_t count_test_arr = 0;

    frame_Message_t frame_respond_data, frame_respond_data_detect;

    uint8_t arr_frame_respond_data[50];

    uint8_t arr_frame_test[0x04 + 8] = {0x55, 0xAA, 0x04, 0x00, 0x0A, 0x00, 0x02, 0x05, 0x64, 0x04, 0x00, 0x64};

    uint8_t length_frame = Message_Create_Frame_Respond_RES(value_test, arr_frame_respond_data);

    printf("/*-------------------------------------------------------------------------------------------------------*/");

    printf("\nStart test respond data\n");

    printf("length_frame = %d\n", length_frame);



    for (count_test_arr = 0; count_test_arr < length_frame; count_test_arr++)

    {



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
