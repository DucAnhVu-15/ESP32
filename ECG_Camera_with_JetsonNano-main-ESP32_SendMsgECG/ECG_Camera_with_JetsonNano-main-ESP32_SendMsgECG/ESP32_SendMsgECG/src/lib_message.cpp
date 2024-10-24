#include "lib_message.h"

uint8_t Message_Create_Frame(ecg_FrameMsg_t data_in, uint8_t *data_out)
{
	uint8_t count_data_out = 0;

	if(data_in.StartFrame != START_BYTE)
	{
		return 0;
	}

	data_out[count_data_out] = (uint8_t)(data_in.StartFrame & 0xFF);
	count_data_out += 1;
	data_out[count_data_out] = (uint8_t)(data_in.StartFrame >> 8);
	count_data_out += 1;
	data_out[count_data_out] = data_in.LengthData;
    count_data_out += 1;

	for (uint8_t i = 0; i < data_in.LengthData - 2; i++)
	{
        data_out[count_data_out] = data_in.Data[i];
        count_data_out += 1;
	}

	data_out[count_data_out] = ECG_CheckSum(data_out, data_in.LengthData + 2);
	count_data_out += 1;
	
	return count_data_out;
}

uint8_t ECG_CheckSum(uint8_t *buf, uint8_t len)
{
    uint8_t sum = 0;
    for (uint8_t i = 2; i < len-1; i++)
    {
        sum = (sum + buf[i]) % 256;
    }
    sum = 0xFF - sum;
    return sum;
}
