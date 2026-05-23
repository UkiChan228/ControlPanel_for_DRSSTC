#ifndef DISPLAY_H
#define display_H

#include "pico/stdlib.h"

// Константы пинов (используем constexpr для C++, либо просто константы для C)
namespace display_gpio {
    // TouchScreen I2C
    const uint I2C0_SDA = 0; // На RP2350 лучше использовать GP0
    const uint I2C0_SCL = 1;
    const uint T_RST    = 4;
    const uint T_INT    = 5;

    // SPI Display
    const uint SPI_SCK  = 10;
    const uint SPI_MOSI = 11;
    const uint SPI_MISO = 12; // Не используется для LCD, но нужен для SD-карты
    const uint LCD_DC   = 13; // Он же RS
    const uint LCD_CS   = 14;
    const uint LCD_RST  = 15;
    const uint LCD_LED  = 16;
}

// Прототипы функций (чтобы main их видел)
void display_hardware_init();
void touch_callback(uint gpio, uint32_t events);

#endif