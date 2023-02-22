#ifndef SET_INTERFACE_HPP 
#define SET_INTERFACE_HPP

#include "stdint.h"

#include "GUI/interface_elements.hpp"

#include "fonts/roboto_all_small.h"
#include "fonts/roboto_numbers_medium.h"


#define SET_RECT_HEIGHT 180
#define SET_RECT_WIDTH 220 
#define SET_RECTS_DISTANCE_HALF 70
#define SET_TRIANGLE_COLOR 160

struct SetScreenConfig{
    const ClockPage * po;
    Rect_t rect_hours;
    Rect_t rect_minutes;
    uint32_t triangle_base;
    uint32_t triangle_height;
    uint32_t triangle_distance;
};

typedef enum {
    JUST_NUMBERS,
    JUST_TRIANGLE,
    BOTH
} SetClearMode;

void draw_set_screen(SetScreenConfig , uint8_t hour, uint8_t min);

void set_screen_draw_fb(SetScreenConfig config, uint8_t number_to_write, Rect_t rectangle_base, uint8_t * fb, bool selected);

void set_screen_draw_h(SetScreenConfig, uint8_t hour, bool);
void set_screen_draw_m(SetScreenConfig, uint8_t minutes, bool);

void set_screen_clear(SetScreenConfig, SetClearMode, Rect_t);

void _draw_filled_triangle(SetScreenConfig &, Rect_t &, const uint8_t &, uint8_t *);

#endif 