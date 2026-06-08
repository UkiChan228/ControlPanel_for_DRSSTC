#include "st7796u_pio.h"
#include "hardware/gpio.h"
#include "../pio/spi_tx.pio.h" 

ST7796::ST7796(PIO _pio, uint _sm, uint8_t _mosi, uint8_t _sck, uint8_t _cs, uint8_t _dc, uint8_t _rst)
    : pio(_pio), sm(_sm), pin_cs(_cs), pin_dc(_dc), pin_rst(_rst) {
    
    gpio_init(pin_cs); gpio_set_dir(pin_cs, GPIO_OUT); gpio_put(pin_cs, 1);
    gpio_init(pin_dc); gpio_set_dir(pin_dc, GPIO_OUT);
    gpio_init(pin_rst); gpio_set_dir(pin_rst, GPIO_OUT); gpio_put(pin_rst, 1);

    uint offset = pio_add_program(pio, &spi_tx_program);
    pio_spi_tx_init(pio, sm, offset, 8, 2, _sck, _mosi);
}

void ST7796::send_cmd(uint8_t cmd) {
    gpio_put(pin_dc, 0); 
    gpio_put(pin_cs, 0);
    pio_sm_put_blocking(pio, sm, (uint32_t)cmd << 24);
    while(!pio_sm_is_tx_fifo_empty(pio, sm));
    gpio_put(pin_cs, 1);
}

void ST7796::send_data(const uint8_t* data, size_t len) {
    gpio_put(pin_dc, 1); 
    gpio_put(pin_cs, 0);
    for (size_t i = 0; i < len; i++) {
        pio_sm_put_blocking(pio, sm, (uint32_t)data[i] << 24);
    }
    while(!pio_sm_is_tx_fifo_empty(pio, sm));
    gpio_put(pin_cs, 1);
}

void ST7796::init() {
    gpio_put(pin_rst, 0); sleep_ms(10);
    gpio_put(pin_rst, 1); sleep_ms(150);

    send_cmd(0x11); sleep_ms(150); // Sleep Out

    uint8_t mactl = 0x48; send_cmd(0x36); send_data(&mactl, 1);
    uint8_t pixfmt = 0x55; send_cmd(0x3A); send_data(&pixfmt, 1);
    
    // Включение дисплея
    send_cmd(0x29); sleep_ms(150);
}

void ST7796::setAddrWindowAndPush(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, const uint16_t* color_data, size_t len) {
    uint8_t d[4];
    
    // CASET
    d[0] = x0 >> 8; d[1] = x0 & 0xFF; d[2] = x1 >> 8; d[3] = x1 & 0xFF;
    send_cmd(0x2A); send_data(d, 4);
    
    // PASET
    d[0] = y0 >> 8; d[1] = y0 & 0xFF; d[2] = y1 >> 8; d[3] = y1 & 0xFF;
    send_cmd(0x2B); send_data(d, 4);
    
    send_cmd(0x2C); // RAMWR
    
    gpio_put(pin_dc, 1);
    gpio_put(pin_cs, 0);
    for(size_t i = 0; i < len; i++) {
        pio_sm_put_blocking(pio, sm, (uint32_t)(color_data[i] >> 8) << 24);
        pio_sm_put_blocking(pio, sm, (uint32_t)(color_data[i] & 0xFF) << 24);
    }
    while(!pio_sm_is_tx_fifo_empty(pio, sm));
    gpio_put(pin_cs, 1);
}