#include "bus_interface.hpp"

void draw_bus(ClockPage po, Trip & t) {

    create_border(po);

    int32_t icon_x = 370 + 10, icon_y = po.margin + po.line_weight + 25;

    /* Draw place marker icon */
    draw_image( 
        icon_x, 
        icon_y, 
        placemarker_height, 
        placemarker_width, 
        placemarker_data, 
        po.framebuffer
    );    

    
    {   /* Draw stopName */  //La farei più piccola, di conseguenza valuta la corretta posizione
        SimpleDimensionVector size = get_text_size(&roboto_all_very_small, t.stopName);
        int32_t
            x_stop = 70 + BIG_ICON_SIZE + BIG_ICON_SIZE + 75,
            y_stop = (icon_y + (placemarker_height >> 1)) + (size.h >> 1);

        writeln( &roboto_all_very_small, t.stopName, &x_stop, &y_stop, po.framebuffer);
    }

    
   { /* Draw destination up name */ //Da modificare la posizione e font
        
        int32_t
            x_stop = 70 + BIG_ICON_SIZE + BIG_ICON_SIZE + 75,
            y_stop = po.margin + po.line_weight + 155;
        
        char busUp[33];
        snprintf(busUp, 33, ">> %s", t.destinationUpName);

        writeln( &roboto_all_very_small, busUp, &x_stop, &y_stop, po.framebuffer );

    }

    { /* Draw destination up buses */ //Da sistemare la posizione, la dimensione va bene
        
        int32_t
            x_stop = 70 + BIG_ICON_SIZE + BIG_ICON_SIZE + 75,
            y_stop = po.margin + po.line_weight + 260;
        
        char arrayBusUp[33] = "";
        char s[8] = "";
        for(int i=0; i<t.n_up; i++){
            sprintf(s, "");
            snprintf(s, 8, "%d\'  ", t.busUp[i]);
            strcat(arrayBusUp, s);
        }

        writeln( &roboto_all_small, arrayBusUp, &x_stop, &y_stop, po.framebuffer );

    }


    { /* Draw destination down name */ //Da modificare la posizione
        
        int32_t
            x_stop = 70 + BIG_ICON_SIZE + BIG_ICON_SIZE + 75,
            y_stop = po.margin + po.line_weight + 330;
        
        char busDown[33];
        snprintf(busDown, 33, ">> %s", t.destinationDownName);

        writeln( &roboto_all_very_small, busDown, &x_stop, &y_stop, po.framebuffer );
    
    }


    { /* Draw destination down buses */  // Da sistemare la posizione
        
        int32_t
            x_stop = 70 + BIG_ICON_SIZE + BIG_ICON_SIZE + 75,
            y_stop = po.margin + po.line_weight + 420;
        
        char arrayBusDown[33] = "";
        char s[8] = "";
        for(int i=0; i<t.n_down; i++){
            sprintf(s, "");
            snprintf(s, 8, "%d\'  ", t.busDown[i]);
            strcat(arrayBusDown, s);
        }

        writeln( &roboto_all_small, arrayBusDown, &x_stop, &y_stop, po.framebuffer );

    }
    
    /* Draw bus icon */
    draw_image_2x( 70, EPD_CENTER_Y - (BIG_ICON_SIZE), BIG_ICON_SIZE, BIG_ICON_SIZE, bus_data, po.framebuffer);

    // Lastly the actual draw
    epd_draw_grayscale_image(epd_full_screen(), po.framebuffer );

    

}

