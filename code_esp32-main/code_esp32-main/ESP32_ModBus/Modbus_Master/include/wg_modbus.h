#ifndef _WG_MODBUS_H_
#define _WG_MODBUS_H_

#include "main.h"

class ModBus
{
    public:
        ~ModBus();
        void Close(void);
        void Free(void);
        void SetSlave(int name_slace);
        int16_t CheckConnect(void);
        int16_t Connect(const char *port, int baudRate);
        int16_t WriteRegister(int addr, int value);
        int16_t ReadRegister(int addr, int nb, uint16_t *dest);
        
    private:
        modbus_t *ctx;
};

#endif
