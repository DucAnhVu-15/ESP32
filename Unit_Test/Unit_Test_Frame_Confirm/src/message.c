#include "message.h"
#include "convert.h"

uint8_t count_check = 0;

uint16_t Message_Frame_Create_Set_Port(port_e datain_port, uint8_t *data_out)
{
    uint8_t *arr_out;
    uint16_t count_set_port_data = 0;
    frame_Message_t frame_set_port;
    arr_out = (uint8_t *)&frame_set_port;
    frame_set_port.StartFrame = START_BYTE;
    frame_set_port.TypeMessage = TYPE_MESSAGE_SET_PORT;
    frame_set_port.Length = LENGTH_MESSAGE_SET_PORT;

    frame_set_port.Data[0] = datain_port;

    for (count_set_port_data = 0; count_set_port_data < LENGTH_DEFAULT + frame_set_port.Length - 2; count_set_port_data++)
    {
        data_out[count_set_port_data] = arr_out[count_set_port_data];
    }

    frame_set_port.CheckFrame = Check_Sum(data_out, LENGTH_DEFAULT + frame_set_port.Length - 2);

    data_out[count_set_port_data] = (frame_set_port.CheckFrame & 0xFF);
    count_set_port_data += 1;
    data_out[count_set_port_data] = ((frame_set_port.CheckFrame >> 8) & 0xFF);
    count_set_port_data += 1;

    return count_set_port_data;
}

/*-----------------------------------Chuyển data của struct sang data của struct với port, sensor-----------------------------------*/
uint8_t Messagee_Frame_Create_Confirm(uint8_t datain_port, uint8_t datain_sensor, uint8_t *dataout)
{
    frame_Message_t frame_confirm;

    uint8_t *sensor_confirm;

    /* ép kiểu arr_frame_confirm về kiểu uint8_t, mục đích để chuyển từ struct sang arr* */
    sensor_confirm = (uint8_t *)&frame_confirm;

    uint16_t count_confirm_data = 0;

    frame_confirm.StartFrame = START_BYTE;
    frame_confirm.TypeMessage = TYPE_MESSAGE_SENSOR_CONFIRM;
    frame_confirm.Length = LENGTH_MESSAGE_CONFIRM;

    frame_confirm.Data[0] = datain_port;
    frame_confirm.Data[1] = datain_sensor;

    frame_confirm.CheckFrame = Check_Sum(sensor_confirm, (LENGTH_DEFAULT + frame_confirm.Length - 2));

    for (count_confirm_data = 0; count_confirm_data < LENGTH_DEFAULT + LENGTH_MESSAGE_CONFIRM - 2; count_confirm_data++)
    {
        dataout[count_confirm_data] = sensor_confirm[count_confirm_data];
    }

    dataout[count_confirm_data] = frame_confirm.CheckFrame & 0xff;
    dataout[count_confirm_data + 1] = ((frame_confirm.CheckFrame >> 8) & 0xff);

    count_confirm_data += 2;
    return count_confirm_data;
}

uint8_t Message_Frame_Create_Ask(port_e datain_port, type_Sensor_e datain_sensor, uint8_t *dataout)
{
    uint8_t *data_ask;
    uint16_t count_ask_data;
    frame_Message_t frame_ask;
    /*Ép kiểu frame_ask về kiểu uint8_t, mục đích để chuyển từ struct -> arr*/
    data_ask = (uint8_t *)&frame_ask;
    /*-------------------------------Khởi tạo giá trị Start-----------------*/
    frame_ask.StartFrame = START_BYTE;

    /*-------------------------------Khởi tạo loại bản tin------------------*/
    frame_ask.TypeMessage = TYPE_MESSAGE_ASK_DATA;

    /*-------------------------------Khởi tạo độ dài bản tin----------------*/
    frame_ask.Length = LENGTH_MESSAGE_ASK_DATA;

    /*-------------------------------Gán thông tin cho bản tin--------------*/

    frame_ask.Data[0] = datain_port;
    frame_ask.Data[1] = datain_sensor;

    /*-------------------------------Tính giá trị checksum------------------*/
    frame_ask.CheckFrame = Check_Sum(data_ask, LENGTH_DEFAULT + frame_ask.Length - 2);

    /*Copy từ mảng data_ask ra mảng dataout*/
    for (count_ask_data = 0; count_ask_data < (LENGTH_DEFAULT + frame_ask.Length - 2); count_ask_data++)
    {
        dataout[count_ask_data] = data_ask[count_ask_data];
    }

    /*Ghi giá trị checksum tính được vào cuối mảng*/
    dataout[count_ask_data] = (frame_ask.CheckFrame & 0xff);
    dataout[count_ask_data + 1] = ((frame_ask.CheckFrame >> 8) & 0xff);
    count_ask_data += 2;
    return count_ask_data;
}

uint8_t Message_Frame_Response_LUX(port_e datain_port, type_Sensor_e datain_sensor, float datain_value, uint8_t *dataout)
{
    uint8_t *data_float_to_byte = Convert_From_Float_To_Bytes(datain_value);
    uint8_t *data_lux;
    uint16_t count_respond_lux = 0;
    frame_Message_t frame_response;
    data_lux = (uint8_t *)&frame_response;

    frame_response.StartFrame = START_BYTE;
    frame_response.TypeMessage = TYPE_MESSAGE_SENSOR_RESPOND_DATA;
    frame_response.Length = LENGTH_MESSAGE_RESPOND_LUX;
    frame_response.Data[0] = datain_port;
    frame_response.Data[1] = datain_sensor;

    frame_response.Data[2] = data_float_to_byte[0];
    frame_response.Data[3] = data_float_to_byte[1];
    frame_response.Data[4] = data_float_to_byte[2];
    frame_response.Data[5] = data_float_to_byte[3];

    frame_response.CheckFrame = Check_Sum(data_lux, (LENGTH_DEFAULT + frame_response.Length - 2));

    for (count_respond_lux = 0; count_respond_lux < (LENGTH_DEFAULT + frame_response.Length - 2); count_respond_lux++)
    {
        dataout[count_respond_lux] = data_lux[count_respond_lux];
    }

    dataout[count_respond_lux] = (frame_response.CheckFrame & 0xff);
    dataout[count_respond_lux + 1] = ((frame_response.CheckFrame >> 8) & 0xff);

    count_respond_lux += 2;

    return count_respond_lux;
}

uint8_t Message_Frame_Response_NTC(port_e datain_port, type_Sensor_e datain_sensor, float datain_value, uint8_t *dataout)
{
    uint8_t *data_float_to_byte = Convert_From_Float_To_Bytes(datain_value);
    uint8_t *data_ntc;
    uint16_t count_respond_ntc = 0;
    frame_Message_t frame_response;
    frame_response.StartFrame = START_BYTE;
    frame_response.TypeMessage = TYPE_MESSAGE_SENSOR_RESPOND_DATA;
    frame_response.Length = LENGTH_MESSAGE_RESPOND_NTC;
    frame_response.Data[0] = datain_port;
    frame_response.Data[1] = datain_sensor;

    frame_response.Data[2] = data_float_to_byte[0];
    frame_response.Data[3] = data_float_to_byte[1];
    frame_response.Data[4] = data_float_to_byte[2];
    frame_response.Data[5] = data_float_to_byte[3];

    data_ntc = (uint8_t *)&frame_response;
    frame_response.CheckFrame = Check_Sum(data_ntc, (LENGTH_DEFAULT + frame_response.Length - 2));
    printf("Data out:  ");
    for (count_respond_ntc = 0; count_respond_ntc < (LENGTH_DEFAULT + frame_response.Length - 2); count_respond_ntc++)
    {
        dataout[count_respond_ntc] = data_ntc[count_respond_ntc];
    }

    dataout[count_respond_ntc] = (frame_response.CheckFrame & 0xff);
    dataout[count_respond_ntc + 1] = ((frame_response.CheckFrame >> 8) & 0xff);

    count_respond_ntc += 2;
    return count_respond_ntc;
}

uint8_t Message_Create_Frame_Respond_RES(uint16_t datain_value, uint8_t *dataout)
{
    uint8_t *data_respond_res;
    uint8_t count_arr;
    frame_Message_t frame_respond_res;
    /* Convert from struct -> array */
    data_respond_res = (uint8_t *)&frame_respond_res;
    /*---------------------------(Start)---------------------------------*/
    frame_respond_res.StartFrame = START_BYTE;
    /*----------(Type Msg: Respond data from sensor res)-----------------*/
    frame_respond_res.TypeMessage = TYPE_MESSAGE_SENSOR_RESPOND_DATA;
    /*--------------------(Length of this msg)---------------------------*/
    frame_respond_res.Length = LENGTH_MESSAGE_RESPOND_RES;
    /*---------------(Write port and sensor to Data)---------------------*/
    frame_respond_res.Data[0] = PORT_B;
    frame_respond_res.Data[1] = SENSOR_RES;
    /*-------------------(Write data after convert)----------------------*/
    uint8_t *data_convert;
    data_convert = Convert_From_Uint16_To_Bytes(datain_value);
    printf("Convert data: %x %x \n", data_convert[0], data_convert[1]);
    /*---------------------------(Write data to Data)---------------------------*/
    for (uint8_t i = 0; i < 2; i++)
    {
        frame_respond_res.Data[i + 2] = data_convert[i];
    }

    /*------------------------(Check sum)-----------------------------*/
    frame_respond_res.CheckFrame = Check_Sum(dataout, LENGTH_DEFAULT + frame_respond_res.Length - LENGTH_DEFAULT);
    printf("Check sum: %x \n", frame_respond_res.CheckFrame);

    /*------------(Copy from data_set_port to dataout)-----------------*/

    for (count_arr = 0; count_arr < (LENGTH_DEFAULT + frame_respond_res.Length - 2); count_arr++)
    {
        dataout[count_arr] = data_respond_res[count_arr];
    }

    /*---------------(Write checksum's value to dataout)----------------*/
    dataout[count_arr] = (frame_respond_res.CheckFrame & 0xff);
    dataout[count_arr + 1] = ((frame_respond_res.CheckFrame >> 8) & 0xff);
    count_arr += 2;
    return count_arr;
}

/*----------------------------------------------Chuyển data của arr sang data của struct-----------------------------------------*/
uint8_t Message_Frame_Detect(uint8_t *sensor_datain, frame_Message_t *sensor_dataout)
{
    uint8_t count_data_out = 0;

    sensor_dataout->StartFrame = Convert_From_Bytes_To_Uint16(sensor_datain[count_data_out], sensor_datain[count_data_out + 1]);
    count_data_out += 2;
    if (sensor_dataout->StartFrame != START_BYTE)
    {
        return 0;
    }

    sensor_dataout->TypeMessage = Convert_From_Bytes_To_Uint16(sensor_datain[count_data_out], sensor_datain[count_data_out + 1]);
    count_data_out += 2;

    sensor_dataout->Length = Convert_From_Bytes_To_Uint16(sensor_datain[count_data_out], sensor_datain[count_data_out + 1]);
    count_data_out += 2;

    for (uint8_t i = 0; i < sensor_dataout->Length - 4; i++)
    {
        sensor_dataout->Data[i] = sensor_datain[count_data_out++];
    }

    sensor_dataout->CheckFrame = Convert_From_Bytes_To_Uint16(sensor_datain[count_data_out], sensor_datain[count_data_out + 1]);

    return sensor_dataout->TypeMessage;
}

/*----------------------------------------------------------------------------------------*/
uint8_t Message_Get_Port(frame_Message_t datain_frame)
{
    return datain_frame.Data[0];
}

uint8_t Message_Get_Type_Sensor(frame_Message_t datain_frame)
{
    return datain_frame.Data[1];
}

uint16_t Message_Get_Data_Sensor_Res(frame_Message_t datain_frame)
{
    return Convert_From_Bytes_To_Uint16(datain_frame.Data[2], datain_frame.Data[3]);
}

float Message_Get_Data_Sensor_Lux(frame_Message_t datain_frame)
{
    return Convert_From_Bytes_To_Float(datain_frame.Data[5], datain_frame.Data[4], datain_frame.Data[3], datain_frame.Data[2]);
}

float Message_Get_Data_Sensor_NTC(frame_Message_t datain_frame)
{
    return Convert_From_Bytes_To_Float(datain_frame.Data[5], datain_frame.Data[4], datain_frame.Data[3], datain_frame.Data[2]);
}

uint8_t *Message_Get_Data_Sensor_RTC(frame_Message_t datain_frame, uint8_t *arr_time_out)
{
    uint8_t i = 0;
    for (i = 0; i < 7; i++)
    {
        arr_time_out[i] = datain_frame.Data[i + 2];
    }
}

uint16_t Check_Sum(uint8_t *buf, uint8_t len)
{
    uint16_t crc = 0xFFFF, pos = 0, i = 0;
    for (pos = 0; pos < len; pos++)
    {
        crc ^= (uint16_t)buf[pos]; // XOR byte into least sig. byte of crc
        for (i = 8; i != 0; i--)   // Loop over each bit
        {
            if ((crc & 0x0001) != 0) // If the LSB is set
            {
                crc >>= 1; // Shift right and XOR 0xA001
                crc ^= 0xA001;
            }
            else // Else LSB is not set
            {
                crc >>= 1; // Just shift right
            }
        }
    }
    return crc;
}
