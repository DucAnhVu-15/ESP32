#include <main.h>

ModBus          WG_Modbus;
MS_Read         WG_Read;

int main() 
{
    Modbus_Init();
    sleep(1);

    while(1)
    {
        if(WG_Modbus.CheckConnect() > 0)
        {
            float data_sensor[16];
            int length = WG_Read.Get_SensorData(data_sensor);
            if (length > 0)
            {
                printf("------------------(Size sensor: %d)------------------\n", length);
                for (int i = 0; i < length; i++)
                {
                    printf("%.2f ", data_sensor[i]);
                }
                printf("\n");
            }

            uint8_t button_state[16];
            length = WG_Read.Get_ButtonState(button_state);
            if (length > 0)
            {
                printf("------------------(Size button: %d)------------------\n", length);
                for (int i = 0; i < length; i++)
                {
                    printf("%d ", button_state[i]);
                }
                printf("\n");
            }
            
            uint16_t data_ping;
            std::string phone_number;
            WG_Read.Get_PingState(&data_ping, &phone_number);
            std::cout << "data_ping: " << data_ping << std::endl << "phone_number: " << phone_number << std::endl;

            float a, b, c;
            WG_Read.Get_CalibParameters(&a, &b, &c);
            printf("a: %.2f, b: %.2f, c: %.2f\n", a, b, c);

            uint16_t data;
            std::string phone;
            WG_Read.Get_Status(&data, &phone);
            std::cout << "data: " << data << std::endl << "phone_number: " << phone << std::endl;

            WG_Modbus.Close();
            sleep(1);
        }
        else
        {
            WG_Modbus.Free();
            sleep(5);
            Modbus_Init();
        }
    }

    return 0;
}

void Modbus_Init(void)
{
    #if ENA_LIB_LOG
        plog::init(plog::debug, "Debug.txt");
    #endif

    WG_Modbus.Connect(PORT_MODBUS_NAME, BAUDRATE_MODBUS);
    WG_Modbus.SetSlave(SLAVE_ADDRESS);
    WG_Modbus.CheckConnect();
}

int MS_Read::Get_SensorData(float arr[])
{
    uint8_t count = 0;
    uint16_t tab_reg[32];
    data_format_float_uint16 data;

    int length = WG_Modbus.ReadRegister(SENSOR_DATA_START_REGISTER, SENSOR_DATA_END_REGISTER - SENSOR_DATA_START_REGISTER + 1, tab_reg);
    if (length > 0)
    {
        for(uint8_t i = 0; i < length/2; i++)
        {
            data.bytes[0] = tab_reg[count];
            count++;
            data.bytes[1] = tab_reg[count];
            count++;
            arr[i] = data.data_float;
        }
        return length/2;
    }
    return RETRUN_ERROR;
}

int MS_Read::Get_ButtonState(uint8_t arr[])
{
    uint8_t count = 0;
    uint16_t tab_reg[8];

    int length = WG_Modbus.ReadRegister(BUTTON_DATA_START_REGISTER, BUTTON_DATA_END_REGISTER - BUTTON_DATA_START_REGISTER + 1, tab_reg);

    if (length > 0)
    {
        for(uint8_t i = 0; i < length; i++)
        {
            uint8_t *byte_array = Convert_From_Uint16_To_Bytes(tab_reg[i]);
            arr[count++] = byte_array[0];
            arr[count++] = byte_array[1];
        }
        return length*2;
    }
    return RETRUN_ERROR;
}

int MS_Read::Get_ButtonChangeState(void)
{
    uint16_t tab_reg[1];
    int length = WG_Modbus.ReadRegister(BUTTON_CHANGE_STATE_REGISTER, 1, tab_reg);

    if (length > 0)
    {
        return tab_reg[0];
    }
    return RETRUN_ERROR;
}

int MS_Read::Get_NewMessage(void)
{
    uint16_t tab_reg[1];
    int length = WG_Modbus.ReadRegister(NEW_MESSAGE_REGISTER, 1, tab_reg);

    if (length > 0)
    {
        return tab_reg[0];
    }
    return RETRUN_ERROR;
}

int MS_Read::Get_PingState(uint16_t *data, std::string *phone_number)
{
    uint16_t tab_reg[6];
    int length = WG_Modbus.ReadRegister(PING_STATUS_START_REGISTER, PING_STATUS_END_REGISTER - PING_STATUS_START_REGISTER + 1, tab_reg);

    if (length > 0)
    {
        *data = tab_reg[0];
        
        for(uint8_t i = 1; i < length; i++)
        {
            uint8_t *byte_array = Convert_From_Uint16_To_Bytes(tab_reg[i]);
            *phone_number += std::to_string(byte_array[0] - '0');
            *phone_number += std::to_string(byte_array[1] - '0');
        }
        return 1;
    }
    return RETRUN_ERROR;
}

int MS_Read::Get_CalibParameters(float *a, float *b, float *c)
{
    uint8_t count = 0;
    uint16_t tab_reg[6];
    data_format_float_uint16 data;

    int length = WG_Modbus.ReadRegister(CALIB_PARAMETERS_START_REGISTER, CALIB_PARAMETERS_END_REGISTER - CALIB_PARAMETERS_START_REGISTER + 1, tab_reg);
    if (length > 0)
    {
        for(uint8_t i = 0; i < length/2; i++)
        {
            data.bytes[0] = tab_reg[count];
            count++;
            data.bytes[1] = tab_reg[count];
            count++;
            
            switch (i)
            {
                case 0:
                    *a = data.data_float;
                break;

                case 1:
                    *b = data.data_float;
                break;

                case 2:
                    *c = data.data_float;
                break;
            }
        }
        return 1;
    }
    return RETRUN_ERROR;
}

int MS_Read::Get_Status(uint16_t *data, std::string *phone_number)
{
    uint16_t tab_reg[6];
    int length = WG_Modbus.ReadRegister(GET_STATUS_START_REGISTER, GET_STATUS_END_REGISTER - GET_STATUS_START_REGISTER + 1, tab_reg);

    if (length > 0)
    {
        *data = tab_reg[0];
        
        for(uint8_t i = 1; i < length; i++)
        {
            uint8_t *byte_array = Convert_From_Uint16_To_Bytes(tab_reg[i]);
            *phone_number += std::to_string(byte_array[0] - '0');
            *phone_number += std::to_string(byte_array[1] - '0');
        }
        return 1;
    }
    return RETRUN_ERROR;
}
