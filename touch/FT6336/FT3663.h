#pragma once
#include "pico/stdlib.h"
#include "hardware/pio.h"

struct touch_point_t {
    uint16_t x, y;
    uint8_t touch_id, event;
};

class FT6336 {
private:
    PIO pio;
    uint sm;
    uint8_t addr;

    // Внутренняя функция для чтения регистров I2C
    uint8_t readRegister(uint8_t reg_addr);

public:
    // Конструктор инициализирует PIO и пины
    FT6336(PIO _pio, uint _sm, uint8_t _sda, uint8_t _scl, uint8_t _addr = 0x38);

    // Возвращает количество активных касаний (0, 1 или 2)
    uint8_t getNrTouches();

    // Записывает координаты в структуру point по номеру пальца (n = 1 или 2)
    void getPoint(uint8_t n, touch_point_t *point);
};