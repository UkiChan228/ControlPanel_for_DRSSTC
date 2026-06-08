#ifndef TOUCH_H
#define touch_H

#include "pico/stlib.h"

namespace touch_gpio {

    // TouchScreen I2C
    const uint I2C_SDA = 1; 
    const uint I2C_SCL = 5;
    const uint T_RST = 4;
    const uint T_INT = 0;
};