#include "lib_convert.h"

/*
    @brief: Chuy?n bi?n ki?u float sang d?ng m?ng byte
    @node: Ch?c nang hàm du?c s? d?ng d? Chuy?n bi?n ki?u float sang d?ng m?ng byte 4 ph?n t?
    @param data: Là m?t bi?n ki?u float c?n du?c chuy?n sang m?ng byte.
    @retval: M?ng bytes.
*/
uint8_t *Convert_From_Float_To_Bytes(float data)
{
    static data_format_float_bytes input_convert;
    input_convert.data_float = data;
    return input_convert.bytes;
}

/*
    @brief: Chuy?n m?ng các bi?n ki?u bytes sang bi?n ki?u float
    @node: Ch?c nang hàm du?c s? d?ng d? Chuy?n m?ng các bi?n ki?u bytes sang bi?n ki?u float
    @param data0: Bi?n d?u tiên c?a m?ng .
    @param data1: Bi?n th? hai c?a m?ng .
    @param data2: Bi?n th? ba c?a m?ng .
    @param data3: Bi?n th? tu c?a m?ng .
    @retval: Bi?n int.
*/
float Convert_From_Bytes_To_Float(uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3)
{
    data_format_float_bytes input_convert;
    input_convert.bytes[3] = data0;
    input_convert.bytes[2] = data1;
    input_convert.bytes[1] = data2;
    input_convert.bytes[0] = data3;
     return input_convert.data_float;
}

/*
    @brief: Chuy?n bi?n ki?u int sang d?ng m?ng byte
    @node: Ch?c nang hàm du?c s? d?ng d? Chuy?n bi?n ki?u int sang d?ng m?ng byte 4 ph?n t?
    @param data: Là m?t bi?n ki?u int c?n du?c chuy?n sang m?ng byte.
    @retval: M?ng bytes.
*/
uint8_t *Convert_From_Int_To_Bytes(int data)
{
    static data_format_int_bytes input_convert;
    input_convert.data_int = data;
    return input_convert.bytes;
}

/*
    @brief: Chuy?n m?ng các bi?n ki?u bytes sang bi?n ki?u int
    @node: Ch?c nang hàm du?c s? d?ng d? Chuy?n m?ng các bi?n ki?u bytes sang bi?n ki?u int
    @param data0: Bi?n d?u tiên c?a m?ng .
    @param data1: Bi?n th? hai c?a m?ng .
    @param data2: Bi?n th? ba c?a m?ng .
    @param data3: Bi?n th? tu c?a m?ng .
    @retval: Bi?n int.
*/
uint32_t Convert_From_Bytes_To_Int(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
    data_format_int_bytes input_convert;
    input_convert.bytes[0] = data1;
    input_convert.bytes[1] = data2;
    input_convert.bytes[2] = data3;
    input_convert.bytes[3] = data4;

    return input_convert.data_int;
}

/*
    @brief: Chuy?n bi?n ki?u uint16_t sang d?ng m?ng byte
    @node: Ch?c nang hàm du?c s? d?ng d? Chuy?n bi?n ki?u uint16_t sang d?ng m?ng byte 4 ph?n t?
    @param data: Là m?t bi?n ki?u uint16_t c?n du?c chuy?n sang m?ng byte.
    @retval: M?ng bytes.
*/
uint8_t *Convert_From_Uint16_To_Bytes(int data)
{
    static data_format_uint8_16_t input_convert;
    input_convert.data_uint16 = data;
    return input_convert.bytes;
}

/*
    @brief: Chuy?n m?ng các bi?n ki?u bytes sang bi?n ki?u uint16_t
    @node: Ch?c nang hàm du?c s? d?ng d? Chuy?n m?ng các bi?n ki?u bytes sang bi?n ki?u uint16_t
    @param data0: Bi?n d?u tiên c?a m?ng .
    @param data1: Bi?n th? hai c?a m?ng .
    @retval: Bi?n Uint16_t.
*/
uint16_t Convert_From_Bytes_To_Uint16(uint8_t data1, uint8_t data2)
{
    data_format_uint8_16_t input_convert;
    input_convert.bytes[0] = data1;
    input_convert.bytes[1] = data2;

    return input_convert.data_uint16;
}