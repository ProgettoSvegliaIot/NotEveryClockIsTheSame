
#include "utils.hpp"

void draw_image_2x(uint32_t pos_x,uint32_t pos_y,uint32_t height,uint32_t width,const uint8_t * image){
    draw_image_2x(pos_x,pos_y,height,width,image, NULL);
}

void draw_image_2x(uint32_t pos_x,uint32_t pos_y,uint32_t height,uint32_t width,const uint8_t * image, uint8_t * fb) {

    uint32_t 
        width_d = width / 2,
        width_dd = width / 4,
        height_d = height / 2;

    Rect_t pos;
    pos.x = pos_x;
    pos.y = pos_y;
    pos.height = height;
    pos.width = width;
    uint8_t * temp = (uint8_t *) calloc(FRAMEBUFFER_DIM(width, height), sizeof(uint8_t));

    for(int i=0, i_d;i<height;i++)
        for(int j=0, j_d;j<(width_d);j++){
            
            j_d = j >> 1;
            i_d = i >> 1;
            
            temp[(width_d * i) + j] = image[(width_d * i_d) + j_d];
        }
    
    if(fb == NULL)
        epd_draw_grayscale_image(pos, temp);
    else 
        epd_copy_to_framebuffer(pos, temp, fb);

    for(uint32_t i=0, i_d;i<height;i++)
        for(uint32_t j=0, j_d;j<(width_d);j++){
            
            j_d = (j >> 1) + width_dd;
            i_d = (i >> 1);

            temp[(width_d * i) + j] = image[(width_d * i_d) + j_d];
        }

    pos.x = pos_x + width;

    if(fb == NULL)
        epd_draw_grayscale_image(pos, temp);
    else 
        epd_copy_to_framebuffer(pos, temp, fb);


    for(uint32_t i=0, i_d;i<height;i++)
        for(uint32_t j=0, j_d;j<(width_d);j++){
            
            j_d = (j >> 1);
            i_d = (i >> 1) + height_d;

            temp[(width_d * i) + j] = image[(width_d * i_d) + j_d];
        }

    pos.x = pos_x;
    pos.y = pos_y + height;

    if(fb == NULL)
        epd_draw_grayscale_image(pos, temp);
    else 
        epd_copy_to_framebuffer(pos, temp, fb);
    
    for(uint32_t i=0, i_d;i<height;i++)
        for(uint32_t j=0, j_d;j<(width_d);j++){
            
            j_d = (j >> 1) + width_dd;
            i_d = (i >> 1) + height_d;

            temp[(width_d * i) + j] = image[(width_d * i_d) + j_d];
        }

    pos.x = width + pos_x;

    if(fb == NULL)
        epd_draw_grayscale_image(pos, temp);
    else 
        epd_copy_to_framebuffer(pos, temp, fb);

    delete[] temp;

}


void draw_image(uint32_t pos_x,uint32_t pos_y,uint32_t height,uint32_t width,const uint8_t * image){
    draw_image(pos_x,pos_y,height,width,image, NULL);
}

void draw_image(uint32_t pos_x,uint32_t pos_y,uint32_t height,uint32_t width,const uint8_t * image, uint8_t * fb) {
    Rect_t pos;
    pos.x = pos_x;
    pos.y = pos_y;
    pos.height = height;
    pos.width = width;

    if(fb == NULL)
        epd_draw_grayscale_image(pos, const_cast<uint8_t *>(image));
    else 
        epd_copy_to_framebuffer(pos, const_cast<uint8_t *>(image), fb);
}

void cpy(char * s1, const char *s2){

    int i=0;

    while(s2[i]!='\0'){
        s1[i]=s2[i];
        i++;
    }

    s1[i]='\0';
}


int stringCmp(char * s1, const char* s2){

    int equal = 0;
    int i=0;

    while(s1[i]!='\0'){
        if(s1[i]==s2[i]) i++;
        else break;
    }

    if(s1[i]=='\0' && s2[i]=='\0') equal=1;

    return equal;

}