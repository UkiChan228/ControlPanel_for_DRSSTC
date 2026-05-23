#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h" // Для управления яркостью LED
#include "display.h"

void display_hardware_init() {
    // 1. Инициализация I2C (для Тачскрина) на скорости 400 кГц
    i2c_init(i2c0, 400 * 1000);
    gpio_set_function(display_gpio::I2C0_SDA, GPIO_FUNC_I2C);
    gpio_set_function(display_gpio::I2C0_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(display_gpio::I2C0_SDA);
    gpio_pull_up(display_gpio::I2C0_SCL);

    // 2. Инициализация SPI (для LCD) на скорости 60 МГц
    spi_init(spi1, 60 * 1000 * 1000); 
    gpio_set_function(display_gpio::SPI_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(display_gpio::SPI_MOSI, GPIO_FUNC_SPI);
    
    // 3. Настройка управляющих пинов LCD
    gpio_init(display_gpio::LCD_CS);
    gpio_set_dir(display_gpio::LCD_CS, GPIO_OUT);
    gpio_put(display_gpio::LCD_CS, 1);

    gpio_init(display_gpio::LCD_DC);
    gpio_set_dir(display_gpio::LCD_DC, GPIO_OUT);

    // 4. Настройка прерывания Тачскрина
    gpio_init(display_gpio::T_INT);
    gpio_set_dir(display_gpio::T_INT, GPIO_IN);
    gpio_pull_up(display_gpio::T_INT);
    
    // Привязываем функцию обратного вызова
    gpio_set_irq_enabled_with_callback(display_gpio::T_INT, GPIO_IRQ_EDGE_FALL, true, &touch_callback);
}

void touch_callback(uint gpio, uint32_t events) {
    // Сюда программа прыгнет сама, когда коснешься экрана
    // Здесь будем читать данные по I2C
}