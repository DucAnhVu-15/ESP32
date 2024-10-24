#ifndef _WG_DEBUG_H_
#define _WG_DEBUG_H_

#include "main.h"

#define ENABLE_DEBUG_MODBUS_ERROR 1
#define ENABLE_DEBUG_MODBUS_STATUS 1

class DebugLogger
{
    public:
        void DebugError(const char *str);
        void DebugStatus(const char *str);
        void DebugLOG(int header, std::vector<std::string> content);
        
    private:
   
};

#endif
