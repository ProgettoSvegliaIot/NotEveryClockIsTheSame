#pragma once 

#include "gui/interface_elements.hpp"
#include <Arduino.h>

#include "fonts/roboto_all_small.h"

// For clear_last_menu
#include "uart/transport_base.hpp"

#define ALARM_TEXT "ALARM"
#define TRANSPORT_TEXT "TRANSPORT"
#define METEO_TEXT "WEATHER"

void draw_menu(ClockPage po, const char * string);

void clear_last_menu(state_t last_state);