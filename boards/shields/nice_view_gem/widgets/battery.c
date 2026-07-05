#include <zephyr/kernel.h>
#include "battery.h"
#include "../assets/custom_fonts.h"

LV_IMG_DECLARE(l_battery_100);
LV_IMG_DECLARE(l_battery_90);
LV_IMG_DECLARE(l_battery_75);
LV_IMG_DECLARE(l_battery_50);
LV_IMG_DECLARE(l_battery_25);
LV_IMG_DECLARE(l_battery_10);


static void draw_level(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_img_dsc_t img_dsc_l;
    lv_draw_img_dsc_init(&img_dsc_l);

    uint8_t level = state->battery;
    if (level > 90) {
        lv_canvas_draw_img(canvas, 8, 10, &l_battery_100, &img_dsc_l);
    } else if (level > 75) {
        lv_canvas_draw_img(canvas, 8, 10, &l_battery_90, &img_dsc_l);
    } else if (level > 50) {
        lv_canvas_draw_img(canvas, 8, 10, &l_battery_75, &img_dsc_l);
    } else if (level > 25) {
        lv_canvas_draw_img(canvas, 8, 10, &l_battery_50, &img_dsc_l);
    } else if (level > 10) {
        lv_canvas_draw_img(canvas, 8, 10, &l_battery_25, &img_dsc_l);
    } else if (level > 1) {
        lv_canvas_draw_img(canvas, 8, 10, &l_battery_10, &img_dsc_l);
    }

}

// A lightning bolt drawn in the free strip above the left battery to signal that
// this (central) half is receiving USB power. Shape is Material's "flash" glyph
// scaled to ~6x10 px; a filled white polygon avoids occluding the battery icon
// the way an opaque INDEXED_1BIT image would. Only drawn when charging.
static void draw_charging(lv_obj_t *canvas, const struct status_state *state) {
    if (!state->charging) {
        return;
    }

    lv_draw_rect_dsc_t bolt_dsc;
    init_rect_dsc(&bolt_dsc, LVGL_FOREGROUND);

    static const lv_point_t bolt[] = {
        {35, 0}, {35, 6}, {37, 6}, {37, 10}, {41, 4}, {39, 4}, {41, 0},
    };
    lv_canvas_draw_polygon(canvas, bolt, ARRAY_SIZE(bolt), &bolt_dsc);
}

void draw_battery_status(lv_obj_t *canvas, const struct status_state *state) {
    draw_level(canvas, state);
    draw_charging(canvas, state);
}