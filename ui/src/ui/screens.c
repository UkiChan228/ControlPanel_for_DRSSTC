#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

objects_t objects;

extern const lv_font_t lv_font_montserrat_20;

//
// Screens
//

void create_screen_main() {
    // Создаем TileView для свайпов и шторки
    lv_obj_t *tileview = lv_tileview_create(0);
    objects.main = tileview;
    lv_obj_set_size(tileview, 480, 320);
    lv_obj_set_style_bg_color(tileview, lv_color_hex(0x1e1e2e), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // === Таил 1: Основной экран ===
    lv_obj_t *tile_main = lv_tileview_add_tile(tileview, 0, 0, LV_DIR_HOR);
    {
        lv_obj_t *pad = lv_obj_create(tile_main);
        lv_obj_set_size(pad, 480, 320);
        lv_obj_set_flex_flow(pad, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_align(pad, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        
        // Логотип Interuptter
        {
            lv_obj_t *logo_box = lv_obj_create(pad);
            lv_obj_set_size(logo_box, 121, 88);
            lv_obj_set_style_bg_opa(logo_box, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(logo_box, lv_color_hex(0x45475a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(logo_box, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(logo_box, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *label = lv_label_create(logo_box);
                lv_obj_set_pos(label, -1, -27);
                lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                add_style_text(label);
                lv_obj_set_style_align(label, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_label_set_text_static(label, "Interuptter");
            }
        }
        
        // Заголовок
        {
            lv_obj_t *title = lv_label_create(pad);
            lv_label_set_text_static(title, "DRSSTC Tesla Coil");
            lv_obj_set_style_text_font(title, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(title, lv_color_hex(0xcdd6f4), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(title, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        
        // Кнопка открытия шторки меню
        {
            lv_obj_t *drawer_btn = lv_button_create(pad);
            lv_obj_set_size(drawer_btn, 100, 50);
            lv_obj_add_flag(drawer_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            {
                lv_obj_t *label = lv_label_create(drawer_btn);
                lv_label_set_text_static(label, "⚙ Настройки");
                lv_obj_center(label);
                add_style_text(label);
            }
            lv_obj_add_event_cb(drawer_btn, action_open_drawer, LV_EVENT_PRESSED, NULL);
        }
        
        // Кнопка About
        {
            lv_obj_t *about_btn = lv_button_create(pad);
            lv_obj_set_size(about_btn, 100, 40);
            lv_obj_add_flag(about_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            {
                lv_obj_t *label = lv_label_create(about_btn);
                lv_label_set_text_static(label, "О программе");
                lv_obj_center(label);
                add_style_text(label);
            }
            lv_obj_add_event_cb(about_btn, action_open_about, LV_EVENT_PRESSED, NULL);
        }
    }
    
    // === Тайл 2: Боковая шторка меню ===
    lv_obj_t *tile_drawer = lv_tileview_add_tile(tileview, 1, 0, LV_DIR_HOR);
    {
        lv_obj_t *drawer = lv_obj_create(tile_drawer);
        lv_obj_set_size(drawer, 280, 320);
        lv_obj_set_style_bg_color(drawer, lv_color_hex(0x181825), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_flex_flow(drawer, LV_FLEX_FLOW_COLUMN);
        
        // Заголовок шторки
        {
            lv_obj_t *title = lv_label_create(drawer);
            lv_label_set_text_static(title, "Меню настроек");
            lv_obj_set_style_text_font(title, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(title, lv_color_hex(0xcdd6f4), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_flex_grow(title, 0);
            lv_obj_align(title, LV_ALIGN_TOP_MID, 10, 10);
        }
        
        // Плейсхолдеры для настроек DRSSTC
        {
            lv_obj_t *settings_box = lv_obj_create(drawer);
            lv_obj_set_size(settings_box, 260, 50);
            lv_obj_set_style_bg_color(settings_box, lv_color_hex(0x11111b), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(settings_box, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(settings_box, lv_color_hex(0x45475a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_flex_grow(settings_box, 0);
            {
                lv_obj_t *label = lv_label_create(settings_box);
                lv_label_set_text_static(label, "Частота: --- kHz");
                lv_obj_center(label);
                add_style_text(label);
            }
        }
        {
            lv_obj_t *settings_box = lv_obj_create(drawer);
            lv_obj_set_size(settings_box, 260, 50);
            lv_obj_set_style_bg_color(settings_box, lv_color_hex(0x11111b), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(settings_box, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(settings_box, lv_color_hex(0x45475a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_flex_grow(settings_box, 0);
            {
                lv_obj_t *label = lv_label_create(settings_box);
                lv_label_set_text_static(label, "Скважность: --%");
                lv_obj_center(label);
                add_style_text(label);
            }
        }
        {
            lv_obj_t *settings_box = lv_obj_create(drawer);
            lv_obj_set_size(settings_box, 260, 50);
            lv_obj_set_style_bg_color(settings_box, lv_color_hex(0x11111b), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(settings_box, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(settings_box, lv_color_hex(0x45475a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_flex_grow(settings_box, 0);
            {
                lv_obj_t *label = lv_label_create(settings_box);
                lv_label_set_text_static(label, "Режим: Авто");
                lv_obj_center(label);
                add_style_text(label);
            }
        }
        
        // Кнопка закрыть
        {
            lv_obj_t *close_btn = lv_button_create(drawer);
            lv_obj_set_size(close_btn, 260, 50);
            lv_obj_add_flag(close_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            {
                lv_obj_t *label = lv_label_create(close_btn);
                lv_label_set_text_static(label, "← Назад");
                lv_obj_center(label);
                add_style_text(label);
            }
            lv_obj_add_event_cb(close_btn, action_open_main, LV_EVENT_PRESSED, NULL);
            lv_obj_set_style_bg_color(close_btn, lv_color_hex(0xe63946), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_translate_x(close_btn, 0, LV_PART_MAIN | LV_STATE_PRESSED);
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}

void create_screen_about() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.about = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x1e1e2e), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Back button (назад)
            lv_obj_t *back_btn = lv_button_create(parent_obj);
            lv_obj_set_pos(back_btn, 20, 20);
            lv_obj_set_size(back_btn, 50, 50);
            lv_obj_add_event_cb(back_btn, action_open_main, LV_EVENT_PRESSED, NULL);
            lv_obj_set_style_bg_opa(back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(back_btn, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(back_btn, lv_color_hex(0xcdd6f4), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *label = lv_label_create(back_btn);
                lv_label_set_text_static(label, "←");
                lv_obj_center(label);
                add_style_text(label);
            }
        }
        {
            // H1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.h1 = obj;
            lv_obj_set_pos(obj, 74, 43);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_text(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xcdd6f4), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Interuptter for DRSSTC Tesla Coil");
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 480, 0);
            lv_obj_set_size(obj, 320, 10);
            lv_bar_set_value(obj, 50, LV_ANIM_ON);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_transform_rotation(obj, 900, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xb4befe), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x181825), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // Authors
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.authors = obj;
            lv_obj_set_pos(obj, 217, 100);
            lv_obj_set_size(obj, 234, 165);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_text(obj, "Authors:\n1)Uki_chan228 Corporated");
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x11111b), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_about();
}

void tick_screen_about() {
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_about,
};

void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 2) {
        tick_screen_funcs[screen_index]();
    }
}

void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

void create_screens() {
    // Set default LVGL theme
    lv_display_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_display_set_theme(dispp, theme);
    
    // Initialize screens
    create_screen_main();
    create_screen_about();
}