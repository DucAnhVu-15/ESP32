#include "src/convert.h"
#include "src/message.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"






void setUp(void)

{

}



void tearDown(void)

{

}



void Test_Create_Frame_Message(void)

{

    uint8_t count_arr_test = 0;

    frame_Master_t frame_master;



    uint8_t arr_frame[50];

    uint8_t arr_frame_test[4 + 6] = {0x55, 0xAA, 0x01, 0x00, 0x06, 0x00, 0x02, 0x01, 0x02, 0x00};

    printf("/*-------------------------------------------------------------------------------------------------------*/");



    frame_master.StartFrame = 0XAA55;

    frame_master.TypeMessage = TYPE_MASTER_START;

    frame_master.LengthData = 6;

    frame_master.Data[0] = 0x02;

    frame_master.Data[1] = 0x01;





    frame_master.CheckFrame = Check_Sum((uint8_t *)&frame_master, (4 + frame_master.LengthData));



    uint8_t length_frame = Message_Create_Frame_Master(frame_master, arr_frame);



    printf("/*-------------------------------------------------------------------------------------------------------*/");

    printf("\nStart test\n");

    printf("/*-------------------------------------------------------------------------------------------------------*/\n");

    printf("length_frame = %d\n", length_frame);



    for (count_arr_test = 0; count_arr_test < length_frame; count_arr_test++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((arr_frame_test[count_arr_test])), (UNITY_INT)(UNITY_UINT8 )((arr_frame[count_arr_test])), (

       ((void *)0)

       ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_UINT8);

        printf("arr_frame_test[%d] = %x\n", count_arr_test, arr_frame_test[count_arr_test]);

    }

    printf("Test passed\n");

    printf("/*-------------------------------------------------------------------------------------------------------*/\n");

}
