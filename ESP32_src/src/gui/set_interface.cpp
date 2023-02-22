#include "set_interface.hpp"

void draw_set_screen(SetScreenConfig config, uint8_t hour, uint8_t min) {

    create_border( *(config.po) );
    
    { /* Draw the title*/
        
        int32_t
            x_title = config.po->margin + 40,
            y_title = config.po->margin + 35 + ROBOTO_ALL_SMALL_HEIGHT;

        writeln(
            &roboto_all_small, 
            "ALARM SET", 
            &x_title, 
            &y_title, 
            config.po->framebuffer 
        );
    }

    uint32_t padding = 15;

    set_screen_draw_fb(config, hour, config.rect_hours, config.po->framebuffer, true);
    set_screen_draw_fb(config, min, config.rect_minutes, config.po->framebuffer, false);

    /* Lastly, draw the buffer to the screen */
    epd_draw_grayscale_image(epd_full_screen(), config.po->framebuffer );

}

void set_screen_clear(SetScreenConfig config, SetClearMode scm, Rect_t rectangle_base){
    switch(scm) {
        case BOTH:
            epd_clear_area_cycles(
                {
                    rectangle_base.x,
                    rectangle_base.y,
                    rectangle_base.width,
                    (int32_t) ( rectangle_base.height + config.triangle_distance + config.triangle_height + 20 )
                },
                1,
                100
            );
            break;
        case JUST_NUMBERS:
            epd_clear_area_cycles(
                rectangle_base, 
                1,
                100
            );
            break;
        case JUST_TRIANGLE:
            _draw_filled_triangle(config, rectangle_base, 80, NULL);
            break;
    }
}

void set_screen_draw_h(SetScreenConfig config, uint8_t hour, bool selected) {
    uint8_t * fb = init_framebuffer();

    set_screen_draw_fb(config, hour, config.rect_hours, fb, selected);
    
    epd_draw_grayscale_image(epd_full_screen(), fb);
    delete[] fb;
}

void set_screen_draw_m(SetScreenConfig config, uint8_t minutes, bool selected) {
    uint8_t * fb = init_framebuffer();

    set_screen_draw_fb(config, minutes, config.rect_minutes, fb, selected);
    
    epd_draw_grayscale_image(epd_full_screen(), fb);
    delete[] fb;
}

void set_screen_draw_fb(SetScreenConfig config, uint8_t number_to_write, Rect_t rectangle_base, uint8_t * fb, bool selected) {

    char s[3] = "  ";
    sprintf(s, "%02d", number_to_write);

    int32_t s_y, s_x;

    SimpleDimensionVector text_size = get_text_size(&roboto_numbers_medium, s);
    
    s_y = rectangle_base.y + ( rectangle_base.height >> 1 ) + ( text_size.h >> 1 );
    s_x = rectangle_base.x + ( rectangle_base.width >> 1 ) - ( text_size.w >> 1 );
    
    writeln(
        &roboto_numbers_medium,
        s,
        &s_x,
        &s_y,
        fb
    );

    if( selected ) _draw_filled_triangle(config, rectangle_base, SET_TRIANGLE_COLOR, fb);
}


void _draw_filled_triangle(SetScreenConfig & config, Rect_t & rectangle_base, const uint8_t & _color, uint8_t * _fb) {

    uint8_t * fb, color;

    if (_fb == NULL){
        fb = init_framebuffer();
        color = 255 - _color;
    }else {
        fb = _fb;
        color = _color;
    }


    epd_fill_triangle(
        rectangle_base.x + (rectangle_base.width >> 1),
        rectangle_base.y + rectangle_base.height + config.triangle_distance,

        rectangle_base.x + (rectangle_base.width >> 1) - (config.triangle_base >> 1),
        rectangle_base.y + rectangle_base.height + config.triangle_distance + config.triangle_height,

        rectangle_base.x + (rectangle_base.width >> 1) + (config.triangle_base >> 1),
        rectangle_base.y + rectangle_base.height + config.triangle_distance + config.triangle_height,
        color,
        fb
    );

    if( _fb == NULL) {
        epd_draw_image(epd_full_screen(), fb, WHITE_ON_WHITE);
        delete[] fb; 
    }
}
