// #ifdef TEST

#include "unity.h"

#include "message.h"
#include "convert.h"    
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
    
    uint8_t arr_frame_test[LENGTH_DEFAULT + LENGTH_MASTER_SET_PORT] = {0x55, 0xAA, 0x01, 0x00, 0x06, 0x00, 0x02, 0x01, 0x02, 0x00};
    printf("/*-------------------------------------------------------------------------------------------------------*/");

    frame_master.StartFrame = START_BYTE;             // Assuming START_BYTE is defined elsewhere
    frame_master.TypeMessage = TYPE_MASTER_START;     // Assuming TYPE_MASTER_START is defined elsewhere
    frame_master.LengthData = LENGTH_MASTER_SET_PORT; // Assuming LENGTH_MASTER_SET_PORT is defined elsewhere
    frame_master.Data[0] = 0x02;
    frame_master.Data[1] = 0x01;

    // Assuming Check_Sum and LENGTH_DEFAULT are defined elsewhere
    frame_master.CheckFrame = Check_Sum((uint8_t *)&frame_master, (LENGTH_DEFAULT + frame_master.LengthData));

    uint8_t length_frame = Message_Create_Frame_Master(frame_master, arr_frame);

    printf("/*-------------------------------------------------------------------------------------------------------*/");
    printf("\nStart test\n");
    printf("/*-------------------------------------------------------------------------------------------------------*/\n");
    printf("length_frame = %d\n", length_frame);

    for (count_arr_test = 0; count_arr_test < length_frame; count_arr_test++)
    {
        TEST_ASSERT_EQUAL_UINT8(arr_frame_test[count_arr_test], arr_frame[count_arr_test]); 
        printf("arr_frame_test[%d] = %x\n", count_arr_test, arr_frame_test[count_arr_test]);
    }
    printf("Test passed\n");
    printf("/*-------------------------------------------------------------------------------------------------------*/\n");
}

// #endif // TEST
