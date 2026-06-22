#include "actions.h"
#include "ui.h"
#include "screens.h"

// Экстерн для доступа к глобальной переменной objects из screens.c
extern objects_t objects;

// LV_UNUSED is not always available in all LVGL configurations
#define LV_UNUSED(x) (void)(x)

// @task: Открыть About экран по нажатию кнопки "О программе"
void action_open_about(lv_event_t * e) {
    LV_UNUSED(e);
    lv_obj_t *tileview = objects.main;
    if (tileview) {
        // Перейти к тайлу Index 2 (About screen) - для TileView используется tileview_set_tile_by_index
        // Но в нашем случае About - отдельный экран, поэтому переход через loadScreen
        loadScreen(SCREEN_ID_ABOUT);
    }
}

// @task: Вернуться на главный экран из любого места (из About или drawer)
void action_open_main(lv_event_t * e) {
    LV_UNUSED(e);
    loadScreen(SCREEN_ID_MAIN);
}

// @task: Открыть боковую шторку меню настроек (свайп вправо или нажатие кнопки)
void action_open_drawer(lv_event_t * e) {
    LV_UNUSED(e);
    lv_obj_t *tileview = objects.main;
    if (tileview) {
        // Переключить на тайл 2 (drawer tile) - горизонтальная навигация вправо
        lv_tileview_set_tile_by_index(tileview, 1, 0, LV_DIR_RIGHT);
    }
}