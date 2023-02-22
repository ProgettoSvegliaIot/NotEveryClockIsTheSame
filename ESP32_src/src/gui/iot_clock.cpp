#include "iot_clock.hpp"

/*
    Parameters:
    - h : The hour as uint8_t
    - m : The minutes as uint8_t
    - buf: The buf, address of the time buffer from the config
*/
void num_to_buf(const uint8_t &h, const uint8_t &m, char *buf){
    buf[0] = (int)(h/10.0) + 48;
    buf[1] = 48 + (h - (buf[0] - 48) * 10);
    buf[2] = ':';
    buf[3] = (int)(m/10.0) + 48;
    buf[4] = 48 + (m - (buf[3] - 48) * 10); 
    buf[5] = '\0';
}

/*
    Takes the time x and y positions from TimeScreenConf.
    Use writeln to write the contents of time buffer (conf.time_buf)
    directly to the screen with TimeScreenConf.bit_font
*/
void write_time(TimeScreenConf conf) {

    int32_t 
        x = conf.pos_x, 
        y = conf.pos_y;

    writeln(conf.big_time_font, conf.time_buf, &x, &y, NULL);

}

void _write_time_white(TimeScreenConf conf) {

    int32_t 
        x = conf.pos_x, 
        y = conf.pos_y;

    write_mode(conf.big_time_font, conf.time_buf, &x, &y, NULL, WHITE_ON_WHITE, NULL);
}

/*
    Takes the alarmOn x and y positions from TimeScreenConf.
    Use writeln to write that directly to the screen with TimeScreenConf.small_font
*/
void write_alarm(TimeScreenConf conf, uint8_t h, uint8_t m, alarm_state_t active ) {

    int32_t 
        x = conf.pos_x_alarmOn, 
        y = conf.pos_y_alarmOn;

    switch(active) {
        case ALARM_ENABLED:
            snprintf(conf.alarmOn_buf, 30, "Alarm at %2d:%02d", h, m);
            break;
        case ALARM_DISABLED:
            snprintf(conf.alarmOn_buf, 30, "Alarm off");
            break;
        case ALARM_SNOOZED:
            snprintf(conf.alarmOn_buf, 30, "Alarm snoozed at %2d:%02d", h, m);
            break;
    }

    writeln(conf.small_font, conf.alarmOn_buf, &x, &y, NULL);
}

void new_time(const uint8_t &new_h, const uint8_t &new_m, NumToChange *ntc, TimeScreenConf config){

    // I created a temporary buffer and i will put the new h and m values
    // there, so i can check the difference between the new buffer and the old one
    char tmp_buf[6];
    num_to_buf(new_h, new_m, tmp_buf);

    // The actual difference checking
    NumToChange to_change = WHOLE_NUMBER;
    

    if ( tmp_buf[1] != config.time_buf[1] ) 
        to_change = FIRST_H_AND_MIN;

    else if ( tmp_buf[3] != config.time_buf[3] )
        to_change = BOTH_MIN;
   
    else if ( tmp_buf[4] != config.time_buf[4] )
        to_change = FIRST_MIN;    

    *ntc = to_change;
    clear_where_needed(*ntc, config);

    memcpy(config.time_buf, tmp_buf, 6);
}


void clear_where_needed(NumToChange to_clear, TimeScreenConf conf ) {

    Rect_t area;

    int clear_times = 2;
    int clear_duration = 200;
    int clear_height = 260;

    // Temporary time buffer to get text bounds of just the text that
    // remains written on the screen    
    char temp_time[6] = "00:00";
    memcpy(temp_time, conf.time_buf, 6);

    // Temporary (?) variables to get text bounds
    int32_t pos_x = conf.pos_x, pos_y = conf.pos_y,
        ret_pos_x, ret_pos_y, ret_h, ret_w;

    switch (to_clear)
    {
        case FIRST_MIN:
            area = {
                .x = conf.pos_x + 188 + 188 + 188 + 70,
                .y = conf.pos_y - 255,
                .width = 188,
                .height = clear_height,
            };
            epd_clear_area_cycles(area, clear_times, clear_duration);
            break;
        case BOTH_MIN:
            area = {
                .x = conf.pos_x + 188 + 188 + 70,
                .y = conf.pos_y - 255,
                .width = 188 + 188,
                .height = clear_height,
            };
            epd_clear_area_cycles(area, clear_times, clear_duration);
            break;
        case FIRST_H_AND_MIN:
            area = {
                .x = conf.pos_x + 188,
                .y = conf.pos_y - 255,
                .width = 188 + 188 + 70 + 188,
                .height = clear_height,
            };
            epd_clear_area_cycles(area, clear_times, clear_duration);
            break;
        
        case WHOLE_NUMBER:
            area = {
                .x = conf.pos_x,
                .y = conf.pos_y - 255,
                .width = 188 + 188 + 70 + 188 + 188,
                .height = clear_height,
            };
            epd_clear_area_cycles(area, clear_times, clear_duration);
            break;
         
        default:
            break;
    }
}