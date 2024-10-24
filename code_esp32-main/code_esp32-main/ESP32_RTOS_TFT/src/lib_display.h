#ifndef _LIB_DISPLAY_H_
#define _LIB_DISPLAY_H_

#include "lib_sys.h"

// Define TFT pins
#define TFT_CLK   18
#define TFT_RST   4
#define TFT_DC    2
#define TFT_CS    5
#define TFT_SDA   23

void TFT_Init(void);

/*
    CSK - 18
    SDA - 23
    RS  - 2
    RST - 4
    CS  - 5
*/

#endif
