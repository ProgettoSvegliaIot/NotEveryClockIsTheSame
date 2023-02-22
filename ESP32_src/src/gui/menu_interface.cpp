#include "menu_interface.hpp"

void draw_menu(ClockPage po, const char * string) {
    po.clear_framebuffer();
    create_border(po);

    SimpleDimensionVector text_size = get_text_size(&roboto_all_small, string);
    int 
        x = EPD_CENTER_X - ( text_size.w >> 1),
        y = EPD_CENTER_Y + ( text_size.h >> 1);

    writeln(
        &roboto_all_small,
        string,
        &x,
        &y,
        po.framebuffer
    );

    po.draw_framebuffer();

}

void clear_last_menu(state_t last_state){
    SimpleDimensionVector text_size;
    int32_t x, y;

    switch(last_state) {
        case ALARM:
            text_size = get_text_size(&roboto_all_small, ALARM_TEXT);
            x = EPD_CENTER_X - ( text_size.w >> 1),
            y = EPD_CENTER_Y + ( text_size.h >> 1);

            write_mode(
                &roboto_all_small,
                ALARM_TEXT,
                &x,
                &y,
                NULL,
                WHITE_ON_WHITE,
                NULL
            );
            break;
        case TRANSPORT:
            text_size = get_text_size(&roboto_all_small, TRANSPORT_TEXT);
            x = EPD_CENTER_X - ( text_size.w >> 1);
            y = EPD_CENTER_Y + ( text_size.h >> 1);

            write_mode(
                &roboto_all_small,
                TRANSPORT_TEXT,
                &x,
                &y,
                NULL,
                WHITE_ON_WHITE,
                NULL
            );
            break;
        case METEO:
            text_size = get_text_size(&roboto_all_small, METEO_TEXT);
            x = EPD_CENTER_X - ( text_size.w >> 1);
            y = EPD_CENTER_Y + ( text_size.h >> 1);

            write_mode(
                &roboto_all_small,
                METEO_TEXT,
                &x,
                &y,
                NULL,
                WHITE_ON_WHITE,
                NULL
            );
            break;
        default:
            DEFAULT_CLEAR_SCREEN;
    }
}