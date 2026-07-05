#include <zephyr/kernel.h>
#include <drivers/behavior.h>
#include <stdio.h>
#include <string.h>

#include "layer.h"
#include "../assets/custom_fonts.h"
#include <zmk/physical_layouts.h>
#include <zmk/keymap.h>
#include <zmk/matrix.h>

// Miryoku's Mac mirror layers occupy indices 10-17 (U_MBASE..U_MFUN). When one of
// them is the highest active layer we're in "Mac mode": show the short layer name
// (MBase -> Base) and draw the Apple logo as the indicator.
#define MIRYOKU_FIRST_MAC_LAYER 10

LV_IMG_DECLARE(apple_logo);

void draw_layer_status(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &quinquefive_24, LV_TEXT_ALIGN_CENTER);

    char fallback_layer_name[16]; 

    const char *layer_name = zmk_keymap_layer_name(zmk_keymap_layer_index_to_id(state->layer_index));

    if (layer_name == NULL || layer_name[0] == '\0') {
        sprintf(fallback_layer_name, "L#%" PRIu8, state->layer_index);
        
        layer_name = fallback_layer_name;
    }

    bool mac_mode = state->layer_index >= MIRYOKU_FIRST_MAC_LAYER;
    if (mac_mode && layer_name[0] == 'M') {
        layer_name++; // drop the 'M' prefix so the name fits on one line (MBase -> Base)
    }

    lv_canvas_draw_text(canvas, 0, 70, SCREEN_WIDTH, &label_dsc, layer_name);

    if (mac_mode) {
        lv_draw_img_dsc_t img_dsc;
        lv_draw_img_dsc_init(&img_dsc);
        lv_canvas_draw_img(canvas, 60, 40, &apple_logo, &img_dsc);
    }
}