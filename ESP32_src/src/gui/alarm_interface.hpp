#ifndef WAKEUP_INTERFACE_HPP
#define WAKEUP_INTERFACE_HPP

#include <cstdint>

/* Fonts used */
#include "fonts/roboto_all_small.h"
#include "fonts/roboto_numbers_medium.h"
#include "fonts/roboto_all_very_small.h"

/* Wake up image */
#include "images/wakeUp.h"

/* To actually draw  */
#include "utils.hpp"
#include "gui/interface_elements.hpp"

#define BIG_ICON_SIZE 150
#define ROBOTO_ALL_SMALL_HEIGHT 61

void draw_wakeUp(ClockPage po);
void draw_turnAlarmOff(ClockPage po);


#endif	