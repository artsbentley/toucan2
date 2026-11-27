#pragma once

#include <lvgl.h>
#include "util.h"

// Draw the current cat frame while idle or entering deep sleep.
void draw_sleep_screen(lv_obj_t *canvas);
bool is_sleep_screen_active(void);

// Showing or hiding the screen resets the animation to its resting pose.
void set_sleep_screen_active(bool active);
void advance_sleep_frame(void);
