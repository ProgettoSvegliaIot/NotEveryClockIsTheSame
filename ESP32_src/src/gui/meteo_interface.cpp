#include "meteo_interface.hpp"


void _draw_correct_weather_icon(Rect_t rect, uint16_t id, uint8_t * fb){

    uint8_t * image;

    if(id>=200 && id<=232){ //Thunderstorm
        image = const_cast<uint8_t* >(thunder_data);
    }
    else if(id>=300 && id<=531){ //Rain
        image = const_cast<uint8_t* >(rain_data);
    }
    else if(id>=600 && id<=622){ //Snow
        image = const_cast<uint8_t* >(snowflake_data);
    }
    else if(id>=701 && id<=781){ //Fog
        image = const_cast<uint8_t* >(fog_data);
    }
    else if(id==800){ //Clear
        image = const_cast<uint8_t* >(sun_data);

    }else if(id==801 || id==802){ //Few clouds
        image = const_cast<uint8_t* >(cloudy_data);
    }
    else if(id==803 || id==804){ //Clouds
        image = const_cast<uint8_t* >(cloud_data);
    }

    draw_image_2x(rect.x, rect.y, rect.height, rect.width, image, fb);
}

void draw_meteo(ClockPage po, int32_t temperature_int, int32_t humidity_int, char place[20], uint16_t weather_id) {

    create_border(po);
    
    int32_t y_temperature = po.margin + 90 + ROBOTO_NUMBERS_MEDIUM_HEIGHT;

    {   /* Draw temperature */

        int32_t
            x_temperature = EPD_WIDTH - (po.margin + 350);

        char temperature[4];
        snprintf(temperature, 4, "%3d", temperature_int);

        writeln( &roboto_numbers_medium, temperature, &x_temperature, &y_temperature, po.framebuffer );

        draw_image(
            temperature[0] != ' ' ? (x_temperature - ( thermo_width + 308 )) : ( x_temperature - ( thermo_width + 235 )) , 
            y_temperature - ( thermo_height >> 1 ) - ( ROBOTO_NUMBERS_MEDIUM_HEIGHT >> 1 ), 
            thermo_height, 
            thermo_width, 
            thermo_data,
            po.framebuffer
        );

        draw_image_2x(x_temperature + 8, y_temperature - ROBOTO_NUMBERS_MEDIUM_HEIGHT, celsius_height, celsius_width, celsius_data, po.framebuffer);
    }

    {   /* Draw the city */

        int32_t
            y_place = po.margin + 32 + 300 + 30 + 61,
            x_place = po.margin + 32;

        writeln( &roboto_all_small, place, &x_place, &y_place, po.framebuffer );
    }

    {   /* Draw the humidity */

        int32_t
            // temperature + the padding
            y_hum = y_temperature + ROBOTO_ALL_SMALL_HEIGHT + 60,
            // width - num, to start from the right, minus the dimensions of the text + the margin + the padding
            x_hum = EPD_WIDTH - (po.margin + 60 + 200),
            humidity_size = humidity_height;
        
        char humidity[5];
        snprintf(humidity, 5, "%3d%%", humidity_int);

        writeln( &roboto_all_small, humidity, &x_hum, &y_hum, po.framebuffer );

        draw_image(
            humidity[0] != ' ' ? ( x_hum - 220 - humidity_size - 20 ) : ( x_hum - 160 - humidity_size - 20 ), 
            y_hum - ( humidity_size >> 1 ) - (ROBOTO_ALL_SMALL_HEIGHT >> 1), 
            humidity_size,
            humidity_size,
            humidity_data,
            po.framebuffer
        );

    }


    /* Draw weather icon */
    Rect_t pos_icon = {
        70, 70, BIG_ICON_SIZE, BIG_ICON_SIZE
    };
    _draw_correct_weather_icon(pos_icon, weather_id, po.framebuffer);

    // Lastly the actual draw
    epd_draw_grayscale_image(epd_full_screen(), po.framebuffer );
}

