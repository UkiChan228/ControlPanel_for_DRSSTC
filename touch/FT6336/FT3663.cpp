#include "FT3663.h"
#include "../pio/i2c.pio.h" 

FT6x36::FT6x36(PIO _pio, uint _sm, uint8_t _sda, uint8_t _scl, uint8_t _addr)
    : pio(_pio), sm(_sm), addr(_addr) {
    uint offset = pio_add_program(pio, &i2c_program);
    pio_i2c_init(pio, sm, offset, _sda, _scl);
}

uint8_t FT6x36::readRegister(uint8_t reg_addr) {
    uint8_t val = 0;
    // true = no_stop 
    pio_i2c_write_blocking(pio, sm, addr, &reg_addr, 1, true); 
    pio_i2c_read_blocking(pio, sm, addr, &val, 1, false);
    return val;
}

uint8_t FT6x36::getNrTouches() {
    uint8_t count = readRegister(0x02) & 0b111; // FT_REG_TD_STATUS
    return (count > 2) ? 0 : count;
}

void FT6x36::getPoint(uint8_t n, touch_point_t *point) {
    uint8_t offset = (n == 1) ? 0x03 : 0x09; // FT_REG_P1_XH and P2_XH
    
    uint8_t xh = readRegister(offset);
    uint8_t xl = readRegister(offset + 1);
    uint8_t yh = readRegister(offset + 2);
    uint8_t yl = readRegister(offset + 3);
    
    point->x = ((xh & 0x0F) << 8) | xl;
    point->y = ((yh & 0x0F) << 8) | yl;
    point->event = xh >> 6;
    point->touch_id = yh >> 4;
}