#include "wg_modbus.h"


/**
   @brief Destroy the Mod Bus:: Mod Bus object

*/
ModBus::~ModBus()
{
  DebugLogger debug;
  debug.DebugStatus("ModBus::ModBus Free");
  modbus_close(ctx);
  modbus_free(ctx);
}

/**
   @brief Connects to a Modbus device using a serial port.

   @param port The serial port to use.
   @param baudRate The baud rate to use for the serial communication.
   @return int16_t Returns 0 on success or an error code if the connection fails.
*/
int16_t ModBus::Connect(const char *port, int baudRate)
{
    DebugLogger debug;
    ctx = modbus_new_rtu(port, baudRate, 'N', 8, 1);

    if (ctx == NULL)
    {
        #if ENABLE_DEBUG_MODBUS_ERROR
            debug.DebugError("ModBus::Connect Unable to create the libmodbus context");
        #endif
        return RETRUN_ERROR;
    }

    #if ENABLE_DEBUG_MODBUS_STATUS
        debug.DebugStatus("ModBus::Connect Create Done");
    #endif
    return 1;
}

/**
   @brief Sets the Modbus slave address that the class instance will communicate with.

   @param name_slave The Modbus slave address to use.
*/
void ModBus::SetSlave(int name_slace)
{
    DebugLogger debug;
    modbus_set_slave(ctx, name_slace);
}

/**
   @brief Checks the connection to the Modbus slave.

   @return Returns 0 if the connection is established, and a negative error code if it is not.
*/
int16_t ModBus::CheckConnect(void)
{
    DebugLogger debug;
    if (modbus_connect(ctx) == -1)
    {
        #if ENABLE_DEBUG_MODBUS_ERROR
            debug.DebugError("ModBus::CheckConnect Error Connecting");
        #endif
        return RETRUN_ERROR;
    }
    return 1;
}

/**
   @brief Reads one or more holding registers from a Modbus slave.

   @param addr The starting address of the registers to be read.
   @param nb The number of registers to be read.
   @param dest Pointer to an array where the read values will be stored.
   @return Returns the number of registers read if successful, or a negative error code if the operation failed.
*/
int16_t ModBus::ReadRegister(int addr, int nb, uint16_t *dest)
{
    int length = 0;
    DebugLogger debug;
    length = modbus_read_registers(ctx, addr, nb, dest);

    if (length == -1)
    {
        #if ENABLE_DEBUG_MODBUS_ERROR
            debug.DebugError("ModBus::ReadRegister Read Error");
        #endif
        return RETRUN_ERROR;
    }
    
    return length;
}

int16_t ModBus::WriteRegister(int addr, int value)
{
    int length = 0;
    DebugLogger debug;
    length = modbus_write_register(ctx, addr, value);
    if (length == -1)
    {
        #if ENABLE_DEBUG_MODBUS_ERROR
            debug.DebugError("ModBus::WriteRegister");
        #endif
        return RETRUN_ERROR;
    }
    return length;
}

/**
   @brief Close the connection to the Modbus device.
*/
void ModBus::Close(void)
{
    modbus_close(ctx);
}

void ModBus::Free(void)
{
    modbus_close(ctx);
    modbus_free(ctx);
}