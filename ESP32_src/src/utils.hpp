#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>
#include <cstdlib>
#include "epd_driver.h"

#define FRAMEBUFFER_DIM(w, h) ((w)*(h)/2)

void draw_image_2x(uint32_t pos_x,uint32_t pos_y,uint32_t height,uint32_t width,const uint8_t * image, uint8_t * fb);
void draw_image(uint32_t pos_x,uint32_t pos_y,uint32_t height,uint32_t width,const uint8_t * image, uint8_t * fb);

void draw_image_2x(uint32_t pos_x,uint32_t pos_y,uint32_t height,uint32_t width,const uint8_t * image);
void draw_image(uint32_t pos_x,uint32_t pos_y,uint32_t height,uint32_t width,const uint8_t * image);

//Copy string2 in string1
void cpy(char * s1, const char *s2); 

//Compare string1 with string2
int stringCmp(char * s1, const char* s2); 

#endif	