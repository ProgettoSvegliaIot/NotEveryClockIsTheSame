#ifndef BUS_INTERFACE_HPP
#define BUS_INTERFACE_HPP

#include <cstdint>

/* Data from api */
#include "api/webConnection.h"

/* Fonts used */
#include "fonts/roboto_all_small.h"
#include "fonts/roboto_numbers_medium.h"
#include "fonts/roboto_all_very_small.h"

/* Bus image */
#include "images/bus.h"
#include "images/placemarker.h"

/* To actually draw  */
#include "utils.hpp"
#include "gui/interface_elements.hpp"

#define BIG_ICON_SIZE 150

void draw_bus(ClockPage po, Trip & t);


#endif	