#pragma once
#include "pico/stdlib.h"
#include "hardware/pio.h"

class ST7796 {
private:
    PIO pio;
    uint sm;
    uint8_t pin_cs, pin_dc, pin_rst;

    // Внутренние функции для SPI транзакций
    void send_cmd(uint8_t cmd);
    void send_data(const uint8_t* data, size_t len);

public:
    // Конструктор инициализирует пины и запускает PIO-программу
    ST7796(PIO _pio, uint _sm, uint8_t _mosi, uint8_t _sck, uint8_t _cs, uint8_t _dc, uint8_t _rst);

    // Первичная инициализация (сброс и отправка команд запуска дисплея)
    void init();

    // Главная функция отрисовки для LVGL
    void setAddrWindowAndPush(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, const uint16_t* color_data, size_t len);
};