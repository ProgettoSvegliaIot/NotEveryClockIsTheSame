
#include "interface_elements.hpp"

uint8_t * init_framebuffer() {
    uint8_t *framebuffer = (uint8_t *)heap_caps_malloc(EPD_WIDTH * EPD_HEIGHT / 2, MALLOC_CAP_SPIRAM);
    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);
    return framebuffer;
}

void ClockPage::clear_framebuffer() {

    if(this->framebuffer != NULL)
        delete[] this->framebuffer;
        
    this->framebuffer = init_framebuffer();
}

void ClockPage::draw_framebuffer() {
    epd_draw_grayscale_image(epd_full_screen(), this->framebuffer);
}

void create_border(ClockPage bo) {
    // Top line
    for(int i=0;i<bo.line_weight;i++)
        epd_draw_hline(
            bo.margin + bo.margin,
            bo.margin + i,
            EPD_WIDTH - (bo.margin + bo.margin + bo.margin + bo.margin),
            0, 
            bo.framebuffer
        );

    // Bottom line
    for(int i=0;i<bo.line_weight;i++)
        epd_draw_hline(
            bo.margin + bo.margin,
            EPD_HEIGHT - bo.margin - i,
            EPD_WIDTH - (bo.margin + bo.margin + bo.margin + bo.margin),
            0, 
            bo.framebuffer
        );
    
    // Left line
    for(int i=0;i<bo.line_weight;i++)
        epd_draw_vline(
            bo.margin + i,
            bo.margin + bo.margin,
            EPD_HEIGHT - (bo.margin + bo.margin + bo.margin + bo.margin),
            0, 
            bo.framebuffer
        );

    // Right line
    for(int i=0;i<bo.line_weight;i++)
        epd_draw_vline(
            EPD_WIDTH - bo.margin - i,
            bo.margin + bo.margin,
            EPD_HEIGHT - (bo.margin + bo.margin + bo.margin + bo.margin),
            0, 
            bo.framebuffer
        );

    // top left corner
    for(int i=0;i<bo.line_weight;i++)
        epd_draw_circle(
            bo.margin + bo.margin,
            bo.margin + bo.margin,
            bo.margin - i,
            0,
            bo.framebuffer
        );
   

    // top right corner
    for(int i=0;i<bo.line_weight;i++)
        epd_draw_circle(
            EPD_WIDTH - bo.margin - bo.margin,
            bo.margin + bo.margin,
            bo.margin - i,
            0,
            bo.framebuffer
        );

    
    // bottom right corner
    for(int i=0;i<bo.line_weight;i++)
        epd_draw_circle(
            EPD_WIDTH - bo.margin - bo.margin,
            EPD_HEIGHT - bo.margin - bo.margin,
            bo.margin - i,
            0,
            bo.framebuffer
        );

    // bottom left corner
    for(int i=0;i<bo.line_weight;i++)
        epd_draw_circle(
            bo.margin + bo.margin,
            EPD_HEIGHT - bo.margin - bo.margin,
            bo.margin - i,
            0,
            bo.framebuffer
        );
    // clear tall
    epd_fill_rect(
        bo.margin + bo.margin,
        bo.margin + bo.line_weight,
        EPD_WIDTH - (bo.margin + bo.margin + bo.margin + bo.margin),
        EPD_HEIGHT - (bo.margin + bo.line_weight + bo.margin + bo.line_weight - 1),
        255,
        bo.framebuffer
    );
    // clear wide
    epd_fill_rect(
        bo.margin + bo.line_weight,
        bo.margin + bo.margin,
        EPD_WIDTH - (bo.margin + bo.line_weight + bo.margin + bo.line_weight - 1),
        EPD_HEIGHT - (bo.margin + bo.margin + bo.margin + bo.margin),
        255,
        bo.framebuffer 
    );
}

void draw_border(ClockPage bo) {

    create_border(bo); 
    bo.draw_framebuffer();
}
/*
    Prints the real size of the given string
*/
SimpleDimensionVector get_text_size(const GFXfont * font, const char * hs) {
    int32_t w, h, x1, y1,
        temp_x = 50,
        temp_y = 50;
    
    get_text_bounds(
        font,
        hs,
        &temp_x,
        &temp_y,
        &x1,
        &y1,
        &w,
        &h,
        NULL
    );

    return {
        w,
        h
    };
}