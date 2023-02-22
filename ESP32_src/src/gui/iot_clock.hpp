#ifndef IOT_CLOCK_HEADER
#define IOT_CLOCK_HEADER

#include "epd_driver.h"
#include <Arduino.h>
#include "gui/interface_elements.hpp"

#include "uart/transport_base.hpp"

#define DATE_FONT_SIZE 60

typedef enum {
    FIRST_MIN,
    BOTH_MIN,
    FIRST_H_AND_MIN,
    WHOLE_NUMBER
} NumToChange;

struct TimeScreenConf {
    uint16_t pos_x;
    uint16_t pos_y;
    const GFXfont * big_time_font;
    char *time_buf;

    uint16_t pos_x_alarmOn;
    uint16_t pos_y_alarmOn;
    const GFXfont * small_font;
    char alarmOn_buf[30];
};

void num_to_buf(const uint8_t &, const uint8_t &, char*);
void write_time(TimeScreenConf);  
void new_time(const uint8_t &new_h, const uint8_t &new_m, NumToChange *, TimeScreenConf);

void write_alarm(TimeScreenConf, uint8_t, uint8_t, alarm_state_t);

void clear_where_needed(NumToChange to_clear, TimeScreenConf);
void _write_time_white(TimeScreenConf);

#endif


