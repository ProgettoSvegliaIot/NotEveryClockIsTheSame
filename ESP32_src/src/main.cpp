#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM !!!"
#endif

#include <Arduino.h>
#include "epd_driver.h"
#include "esp_adc_cal.h"
#include <FS.h>
#include <SPI.h>
#include <SD.h>

#define WELCOME_TEXT "Welcome"
#define WELCOME_UNDERTEXT "to your new IOT digital alarm clock"

/* Fonts */
#include "fonts/roboto_numbers.h"
#include "fonts/roboto_all_small.h"

/* UART comunication libraries and configurations */
#include "uart/transport_base.hpp"
#include "uart/transport_timestamp.hpp"
#include "uart/uart_communication.hpp"
uint8_t recv[BASE_STRUCT_SIZE_SERIALIZED], recv_int;

/* Various GUI definitions */
#include "gui/interface_elements.hpp"
#include "gui/menu_interface.hpp"
#include "gui/meteo_interface.hpp"
#include "gui/bus_interface.hpp"
#include "gui/alarm_interface.hpp"

/* Global page options*/
ClockPage border_options = {
    38,
    NULL,
    3
};

/* Clock interface, import and configuration */
#include "gui/iot_clock.hpp"
char time_buf[6] = "00:00";

NumToChange ntc;
const TimeScreenConf time_screen_config = {
    60,
    90+255,
    &roboto_numbers,
    time_buf,

    60,
    (int)((540-345-DATE_FONT_SIZE)/2)+DATE_FONT_SIZE+345,
    &roboto_all_small,
    ""
};

/* Alarm set interface, import and configuration */
#include "gui/set_interface.hpp"
const SetScreenConfig set_screen_config = {
    &border_options,

    { /* RECT HOURS */
        EPD_CENTER_X - (SET_RECT_WIDTH + SET_RECTS_DISTANCE_HALF),
        EPD_CENTER_Y - 50,

        SET_RECT_WIDTH,
        SET_RECT_HEIGHT
    },

    { /* RECT MINUTES */
        EPD_CENTER_X + SET_RECTS_DISTANCE_HALF,
        EPD_CENTER_Y - 50,

        SET_RECT_WIDTH,
        SET_RECT_HEIGHT
    },

    44, /* Base */
    28, /* Height */
    16 /* Distance from numbers */

};

/* Network requests libraries and configuration */
#include "api/webConnection.h"
Weather w;
Trip t;

WiFiClient client;

/* Configuration for the "state machine" */
state_t actual_state = INIT;
bool alarm_active = false;

void setup()
{
    // Debugging purpose
    Serial.begin(115200);
    
    // Init the screen
    epd_init();
    epd_clear();
    border_options.clear_framebuffer();

    // Init uart interface
    uart_init();

    SimpleDimensionVector size = get_text_size(&roboto_all_small, WELCOME_TEXT);
    int32_t temp_x = EPD_CENTER_X - (size.w >> 1), temp_y = EPD_CENTER_Y - 50; //Coordinates connecting strings
    uint32_t timeStamp;

    writeln(
        &roboto_all_small, 
        WELCOME_TEXT,
        &temp_x,
        &temp_y,
        NULL
    );
    
    
    WifiConnection();

    // Get timestamp value from API
    timestampAPIconnection(&timeStamp);
    
    Serial.printf("Current time: %d\n", timeStamp); 

    size = get_text_size(&roboto_all_very_small, WELCOME_UNDERTEXT);
    temp_y = EPD_CENTER_Y + (ROBOTO_ALL_VERY_SMALL_HEIGHT) + 30;
    temp_x = EPD_CENTER_X - (size.w >> 1);

    writeln(
        &roboto_all_very_small, 
        WELCOME_UNDERTEXT,
        &temp_x,
        &temp_y,
        NULL
    );

    //To serialize and send timeStamp
    int8_t ser_time[TIMESTAMP_SIZE_SERIALIZED];
    serialize_time(timeStamp, ser_time);
    uart_send(ser_time, TIMESTAMP_SIZE_SERIALIZED);

    Serial.println("Data sent");
}

void loop()
{
    uart_receive(recv, BASE_STRUCT_SIZE_SERIALIZED, &recv_int);

    base * b = deserialize(recv);

    if(
        b->state != actual_state ||
        b->state == HOME || 
        b->state == SET_ALARM_H ||
        b->state == SET_ALARM_M ||
        b->state == SET_TRANSPORT
    ){
        
        switch(b->state){
            case INIT:
                break;
            case HOME:

                if(actual_state == HOME){
                    // If it's the second time we end up in the home
                    new_time(b->ora, b->minuti, &ntc, time_screen_config);
                } else {
                    epd_clear_area_cycles(epd_full_screen(), 2, 150);
                    num_to_buf(b->ora, b->minuti, time_screen_config.time_buf);
                }

                write_time(time_screen_config);
                if(actual_state != HOME) {
                    write_alarm(time_screen_config, b->set_h, b->set_m, b->alarm_on);
                }
                break;
            case ALARM:
                clear_last_menu(actual_state);
                draw_menu(border_options, ALARM_TEXT);
                break;
            case TRANSPORT:
                clear_last_menu(actual_state);
                draw_menu(border_options, TRANSPORT_TEXT);
                break;
            case METEO:
                clear_last_menu(actual_state);
                draw_menu(border_options, METEO_TEXT);
                break;
            case SET_ALARM_H:

                switch(actual_state) {
                    case SET_ALARM_M:
                        set_screen_clear(set_screen_config, JUST_TRIANGLE, set_screen_config.rect_minutes);
                        set_screen_draw_h(set_screen_config, b->set_h, true);
                        break;
                    case SET_ALARM_H:
                        set_screen_clear(set_screen_config, JUST_NUMBERS, set_screen_config.rect_hours); // Evitabile, l'ora non dovrebbe essere cambiata
                        set_screen_draw_h(set_screen_config, b->set_h, false);
                        break;
                    default:
                        DEFAULT_CLEAR_SCREEN;
                        draw_set_screen(set_screen_config, b->set_h, b->set_m);
                        break;
                }

                break;
            case SET_ALARM_M:

                switch(actual_state) {
                    case SET_ALARM_H:
                        set_screen_clear(set_screen_config, JUST_TRIANGLE, set_screen_config.rect_hours);
                        set_screen_draw_m(set_screen_config, b->set_m, true);
                        break;
                    case SET_ALARM_M:
                        set_screen_clear(set_screen_config, JUST_NUMBERS, set_screen_config.rect_minutes); // Evitabile, l'ora non dovrebbe essere cambiata
                        set_screen_draw_m(set_screen_config, b->set_m, false);
                        break;
                    default:
                        break;
                }
                break;
            case SET_TRANSPORT:
                if( actual_state != SET_TRANSPORT ) {
                    DEFAULT_CLEAR_SCREEN;
                    transportAPIconnection(client, &t);
                } else {
                    transportAPIconnection(client, &t);
                    DEFAULT_CLEAR_SCREEN;
                }
                
                draw_bus(border_options, t);

                break;
            case SET_METEO:
                DEFAULT_CLEAR_SCREEN;

                weatherAPIconnection(client, &w);

                draw_meteo(border_options, w.temperature, atoi(w.humidity), w.place, w.weather_id);
                break;
            case DRINN:
                DEFAULT_CLEAR_SCREEN;
                draw_wakeUp(border_options);             
                break;
            case REMOVE_ALARM:  //Da trasformare nello stato di disabilitazione dell'alarm
                DEFAULT_CLEAR_SCREEN;
                draw_turnAlarmOff(border_options);
                break;
        }

        actual_state = b->state;
        alarm_active = b->alarm_on;
    }
    
}

