#include "sleep.h"
#include "../assets/custom_fonts.h"

static bool show_sleep_screen;
static uint8_t frame;

bool is_sleep_screen_active(void) { return show_sleep_screen; }

void set_sleep_screen_active(bool active) {
    show_sleep_screen = active;
    frame = 0;
}

void advance_sleep_frame(void) { frame = (frame + 1) % 8; }

static void stroke(lv_obj_t *canvas, const lv_point_t *points, uint32_t count,
                   lv_color_t color, uint8_t width) {
    lv_draw_line_dsc_t line;
    init_line_dsc(&line, color, width);
    line.round_start = true;
    line.round_end = true;
    lv_canvas_draw_line(canvas, points, count, &line);
}

void draw_sleep_screen(lv_obj_t *canvas) {
    // Small, slow breaths; the last frame remains on the memory LCD in deep sleep.
    const lv_coord_t breath = (frame >= 2 && frame <= 5) ? 2 : 0;
    lv_draw_rect_dsc_t fur;
    init_rect_dsc(&fur, LVGL_FOREGROUND);
    fur.radius = LV_RADIUS_CIRCLE;

    // Curled body, followed by pointed ears and a round, tucked-in head.
    lv_canvas_draw_rect(canvas, 43, 83 - breath, 76, 44 + breath, &fur);
    lv_point_t ears[] = {{29, 98}, {29, 73}, {48, 87}, {59, 74}, {66, 101}};
    lv_canvas_draw_polygon(canvas, ears, 5, &fur);
    lv_canvas_draw_rect(canvas, 24, 86, 47, 37, &fur);

    // Sleepy closed eyes and a smug double-curled cat mouth, without a nose.
    const lv_point_t left_eye[] = {{32, 102}, {36, 105}, {40, 102}};
    const lv_point_t right_eye[] = {{50, 102}, {54, 105}, {58, 102}};
    const lv_point_t mouth[] = {{39, 112}, {40, 114}, {43, 115}, {46, 112},
                                {49, 115}, {52, 114}, {53, 112}};
    stroke(canvas, left_eye, 3, LVGL_BACKGROUND, 2);
    stroke(canvas, right_eye, 3, LVGL_BACKGROUND, 2);
    stroke(canvas, mouth, 7, LVGL_BACKGROUND, 2);

    // A curled tail and little paws resting on its tip.
    const lv_point_t tail[] = {{106, 105}, {109, 113}, {104, 120},
                               {92, 122}, {71, 122}, {65, 119}};
    stroke(canvas, tail, 6, LVGL_BACKGROUND, 3);
    lv_canvas_draw_rect(canvas, 37, 118, 23, 10, &fur);
    const lv_point_t paw[] = {{45, 123}, {45, 127}};
    stroke(canvas, paw, 2, LVGL_BACKGROUND, 1);

    // Three hand-drawn Zs float upward, avoiding dependence on font glyph sizes.
    for (uint8_t i = 0; i < 3; i++) {
        lv_coord_t x = 72 + i * 15;
        lv_coord_t y = 72 - i * 17 - frame;
        lv_coord_t size = 5 + i * 2;
        const lv_point_t z[] = {{x, y}, {x + size, y},
                                {x, y + size}, {x + size, y + size}};
        stroke(canvas, z, 4, LVGL_FOREGROUND, 2);
    }

    lv_draw_label_dsc_t label;
    init_label_dsc(&label, LVGL_FOREGROUND, &quinquefive_8, LV_TEXT_ALIGN_CENTER);
    lv_canvas_draw_text(canvas, 0, 145, SCREEN_WIDTH, &label, "SLEEP");
}
