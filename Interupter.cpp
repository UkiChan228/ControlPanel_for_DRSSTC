#include <stdio.h>
#include "pico/stdlib.h"

#include "display.h"      // Подключаем заголовок, а не .c файл!

#include "hardware/pio.h"
#include "interupter.pio.h"    // Этот файл создаст CMake из твоего .pio

int main() {
    stdio_init_all(); // Чтобы работал printf через USB

    // Инициализируем всё железо экрана
    display_hardware_init();

    printf("Pico 2 Interrupter Started!\n");



    while (true) {
        // Тут работает LVGL или твоя логика меню
        tight_loop_contents(); 
    }
}