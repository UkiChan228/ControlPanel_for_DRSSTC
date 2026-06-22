#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// @task: Открыть About экран по нажатию кнопки "О программе"
extern void action_open_about(lv_event_t * e);

// @task: Вернуться на главный экран из любого места (из About или drawer)
extern void action_open_main(lv_event_t * e);

// @task: Открыть боковую шторку меню настроек (свайп вправо или нажатие кнопки)
extern void action_open_drawer(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/