#ifndef DISPLAY_H
#define display_H

#include "pico/stdlib.h"

// Константы пинов (используем constexpr для C++, либо просто константы для C)
namespace display_gpio {
    // TouchScreen I2C
    const uint I2C0_SDA = 1; 
    const uint I2C0_SCL = 5;
    const uint T_RST    = 4;
    const uint T_INT    = 0;

    // SPI Display
    const uint SPI_SCK  = 10;
    const uint SPI_MOSI = 11;
    const uint SPI_MISO = 13; 
    const uint LCD_CS   = 15;
    const uint LCD_RST  = 14;
    const uint LCD_LED  = 15;
}

// Прототипы функций (чтобы main их видел)
void display_hardware_init();
void touch_callback(uint gpio, uint32_t events);

#endif