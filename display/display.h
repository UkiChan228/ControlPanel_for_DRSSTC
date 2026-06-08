#ifndef DISPLAY_H
#define display_H

#include "pico/stdlib.h"

namespace display_gpio {

    // SPI Display
    const uint SPI_SCK  = 10;
    const uint SPI_MOSI = 11;
    const uint SPI_MISO = 8; 
    const unit SPI_RS = 13;
    const uint LCD_CS = 15;
    const uint LCD_RST = 14;
    const uint LCD_LED = 9;
}

