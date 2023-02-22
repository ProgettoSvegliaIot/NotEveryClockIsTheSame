#include "alarm_interface.hpp"

void draw_wakeUp(ClockPage po){

    create_border(po);

    /* Draw wake up icon */
    draw_image_2x( 90, EPD_CENTER_Y - (BIG_ICON_SIZE), BIG_ICON_SIZE, BIG_ICON_SIZE, wakeUp_data, po.framebuffer);

    { //Draw wake up string
        char stringa[30] = "Wake up!";
        int32_t
                x_stop = 70 + BIG_ICON_SIZE + BIG_ICON_SIZE + 110,
                y_stop = po.margin + po.line_weight + 260;
        writeln( &roboto_all_small, stringa, &x_stop, &y_stop, po.framebuffer );
    }

    { //Draw direction
        char stringa[70] = "Press yellow to snooze";
        SimpleDimensionVector size = get_text_size(&roboto_all_very_small, stringa);

        int32_t
                y_stop = 70 + BIG_ICON_SIZE + BIG_ICON_SIZE + 110,
                x_stop = EPD_CENTER_X - (size.w >> 1);
                

        writeln( &roboto_all_very_small, stringa, &x_stop, &y_stop, po.framebuffer );
    }

    // Lastly the actual draw
    epd_draw_grayscale_image(epd_full_screen(), po.framebuffer );
}


void draw_turnAlarmOff(ClockPage po){

    create_border(po);

     { //Draw string
        char stringa[70] = "Disable the alarm?";
        SimpleDimensionVector size = get_text_size(&roboto_all_small, stringa);

        int32_t
                y_stop = EPD_CENTER_Y + ROBOTO_ALL_SMALL_HEIGHT/2,
                x_stop = EPD_CENTER_X - (size.w >> 1);
                

        writeln( &roboto_all_small, stringa, &x_stop, &y_stop, po.framebuffer );
    }

    { //Draw direction
        char stringa[70] = "Press OK to confirm";
        SimpleDimensionVector size = get_text_size(&roboto_all_very_small, stringa);

        int32_t
                y_stop = 70 + BIG_ICON_SIZE + BIG_ICON_SIZE + 110,
                x_stop = EPD_CENTER_X - (size.w >> 1);
                

        writeln( &roboto_all_very_small, stringa, &x_stop, &y_stop, po.framebuffer );
    }

    // Lastly the actual draw
    epd_draw_grayscale_image(epd_full_screen(), po.framebuffer );

}