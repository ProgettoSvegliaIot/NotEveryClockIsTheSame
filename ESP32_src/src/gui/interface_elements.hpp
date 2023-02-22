#ifndef INTERFACE_ELEMENTS_HPP
#define INTERFACE_ELEMENTS_HPP

#include "epd_driver.h"
#include <Arduino.h>

#define DEFAULT_CLEAR_SCREEN epd_clear_area_cycles(epd_full_screen(), 2, 80);

#define EPD_CENTER_Y ( EPD_HEIGHT >> 1 )
#define EPD_CENTER_X ( EPD_WIDTH >> 1 )

struct ClockPage {
    uint16_t margin;
    uint8_t *framebuffer;
    uint16_t line_weight;

    void clear_framebuffer();
    void draw_framebuffer();
};

struct SimpleDimensionVector {
    uint16_t w;
    uint16_t h;
};

uint8_t * init_framebuffer();
void draw_border(ClockPage);
void create_border(ClockPage);

SimpleDimensionVector get_text_size(const GFXfont * font, const char * hs);

#endif
