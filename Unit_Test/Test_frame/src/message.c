#include "message.h"

/*mảng này dùng để kiểm tra xem sensor chọn là loại nào*/
static list_Sensor_e sensor_list_arr[SIZE_LIST_SENSOR] = {SENSOR_NTC, SENSOR_RHEOSTAT, SENSOR_DS1307, SENSOR_LIGTH};

/*mảng này để biết data chiếm bao nhiêu byte để thực hiện cộng với length*/
static uint8_t length_sensor_arr[SIZE_LIST_SENSOR] = {4, 4, 4, 4};

uint8_t Message_Create_Frame_Master(frame_Master_t DataIn, uint8_t *DataOut)
{
    uint8_t *master_datain;
    frame_Master_t *master_data;

    /*dùng con trỏ frame_sensor_t trỏ đến DataIn*/
    master_data = &DataIn;

    /* ép kiểu arr_datain về kiểu uint8_t, mục đích để chuyển từ struct sang arr* */
    master_datain = (uint8_t *)master_data;

    uint16_t count_master_data = 0;

    if (DataIn.StartFrame != START_BYTE)
    {
        return 0;
    }

    switch (DataIn.TypeMessage)
    {
        case TYPE_MASTER_START:
            DataIn.LengthData = LENGTH_MASTER_SET_PORT;
            break;
        case TYPE_MASTER_ASK_DATA:
            DataIn.LengthData = LENGTH_MASTER_ASK_DATA;
            break;
    }
    DataIn.CheckFrame = Check_Sum(master_datain, (LENGTH_DEFAULT + DataIn.LengthData));

    for (count_master_data = 0; count_master_data < (LENGTH_DEFAULT + DataIn.LengthData); count_master_data++)
    {
        DataOut[count_master_data] = master_datain[count_master_data];
    }
    DataOut[count_master_data] = DataIn.CheckFrame & 0xff;
    DataOut[count_master_data + 1] = ((DataIn.CheckFrame >> 8) & 0xff);

    count_master_data += 2;
    return count_master_data;
}

uint8_t Message_Detech_Frame_Master(uint8_t *Master_DataIn, frame_Master_t *Master_DataOut)
{
    frame_Master_t *frame_master_data;
    frame_master_data = (frame_Master_t *)Master_DataIn;

    uint16_t master = 0;

    Master_DataOut->StartFrame = Convert_From_Bytes_To_Uint16(Master_DataIn[master], Master_DataIn[master++]);
    master += 2;

    Master_DataOut->TypeMessage = Master_DataIn[master];
    master += 1;

    Master_DataOut->LengthData = Convert_From_Bytes_To_Uint16(Master_DataIn[master], Master_DataIn[master++]);
    master += 2;

    if (Master_DataOut->TypeMessage == TYPE_MESSAGE_SENSOR_SENDDATA)
    {
        for (int count_data_master = 0; count_data_master < 4; count_data_master++)
        {
            Master_DataOut->Data[count_data_master] = Master_DataIn[master++];
        }
    }

    Master_DataOut->CheckFrame = Convert_From_Bytes_To_Uint16(Master_DataIn[master], Master_DataIn[master++]);
}

uint8_t Message_Create_Frame_Slave(frame_Sensor_t DataIn, uint8_t *DataOut)
{
    uint8_t *arr_datain;
    frame_Sensor_t *sensor_data;

    /*dùng con trỏ frame_sensor_t trỏ đến DataIn*/
    sensor_data = &DataIn;

    /* ép kiểu arr_datain về kiểu uint8_t, mục đích để chuyển từ struct sang arr* */
    arr_datain = (uint8_t *)sensor_data;

    uint8_t count_arr_data = 0;
    uint16_t count_arr = 0;

    if (DataIn.StartFrame != START_BYTE)
    {
        return 0;
    }

    switch (DataIn.TypeMessage)
    {
    case TYPE_MESSAGE_SENSOR_RESPOND:
        DataIn.LengthData = LENGTH_SENSOR_RESPOND;
        break;
    case TYPE_MESSAGE_SENSOR_SENDDATA:
        DataIn.LengthData = LENGTH_SENSOR_SEND_DATA;
        for (count_arr = 0; count_arr < SIZE_LIST_SENSOR; count_arr++)
        {
            if (DataIn.Data[0] == sensor_list_arr[count_arr])
            {
                DataIn.LengthData = LENGTH_SENSOR_SEND_DATA + length_sensor_arr[count_arr];
            }
        }
        break;
    }
    DataIn.CheckFrame = Check_Sum(arr_datain, (LENGTH_DEFAULT + DataIn.LengthData));

    /*Copy từ mảng arr_data ra mảng DataOut*/
    for (uint8_t count_arr_data = 0; count_arr_data < (LENGTH_DEFAULT + DataIn.LengthData); count_arr_data++)
    {
        DataOut[count_arr_data] = arr_datain[count_arr_data];
    }

    /*Ghi giá trị checksum tính được vào cuối mảng*/
    DataOut[count_arr_data] = DataIn.CheckFrame & 0xff;
    DataOut[count_arr_data + 1] = ((DataIn.CheckFrame >> 8) & 0xff);

    /*tăng giá trị mảng lên 2 lần vì đã thêm ở trên*/
    count_arr_data += 2;

    return count_arr_data;
}

uint8_t Message_Detech_Frame_Slave(uint8_t *Sensor_DataIn, frame_Sensor_t *Sensor_DataOut)
{
    frame_Sensor_t *frame_sensor_data;
    frame_sensor_data = (frame_Sensor_t *)Sensor_DataIn;

    uint8_t data_sensor[2];
    uint8_t count_data_out = 0;

    Sensor_DataOut->StartFrame = Convert_From_Bytes_To_Uint16(Sensor_DataIn[count_data_out], Sensor_DataIn[count_data_out++]);
    count_data_out += 2;

    Sensor_DataOut->TypeMessage = Sensor_DataIn[count_data_out];
    count_data_out += 1;

    Sensor_DataOut->LengthData = Sensor_DataIn[count_data_out];
    count_data_out += 1;

    switch (Sensor_DataOut->TypeMessage)
    {
    case TYPE_MESSAGE_SENSOR_RESPOND:
        for (uint8_t i = 0; i < Sensor_DataOut->LengthData; i++)
        {
            Sensor_DataOut->Data[i] = Sensor_DataIn[count_data_out];
            count_data_out += 1;
        }
        break;
    case TYPE_MESSAGE_SENSOR_SENDDATA:
        for (uint8_t i = 0; i < Sensor_DataOut->LengthData; i++)
        {
            Sensor_DataOut->Data[i] = Sensor_DataIn[count_data_out];
            count_data_out += 1;
        }
        break;
    default:
        break;
    }

    Sensor_DataOut->CheckFrame = Convert_From_Bytes_To_Uint16(Sensor_DataIn[count_data_out], Sensor_DataIn[count_data_out++]);

    return 0;
}


uint8_t Check_Sum(uint8_t *buf, uint8_t len)
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