#ifndef METEO_INTERFACE_HPP
#define METEO_INTERFACE_HPP

#include <cstdint>

/* Fonts used */
#include "fonts/roboto_all_small.h"
#include "fonts/roboto_numbers_medium.h"

/* Images shown */
#include "images/rain.h"
#include "images/thermo.h"
#include "images/celsius.h"
#include "images/cloud.h"
#include "images/cloudy.h"
#include "images/fog.h"
#include "images/snowflake.h"
#include "images/sun.h"
#include "images/thunder.h"

#include "images/humidity.h"

/* To actually draw  */
#include "utils.hpp"
#include "gui/interface_elements.hpp"

#define BIG_ICON_SIZE 150

void draw_meteo(ClockPage po, int32_t, int32_t, char place[20], uint16_t);


#endif	