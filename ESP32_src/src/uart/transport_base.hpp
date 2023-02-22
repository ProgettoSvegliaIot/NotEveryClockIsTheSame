#ifndef SM_H_
#define SM_H_

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

/* Base struct sizes */
#define BASE_STRUCT_SIZE_SERIALIZED 6

typedef enum { ALARM_DISABLED, ALARM_ENABLED, ALARM_SNOOZED } alarm_state_t;
typedef enum{ INIT, HOME, ALARM, TRANSPORT, METEO, SET_ALARM_H, SET_ALARM_M, SET_TRANSPORT, SET_METEO, DRINN, REMOVE_ALARM }state_t;

typedef struct base{
    state_t state;
    uint8_t ora;
    uint8_t minuti;

    uint8_t set_h;
    uint8_t set_m;
    alarm_state_t alarm_on;

    base(){
        ora=0;
        minuti=0;
        state=(state_t)0;
        set_h = 0;
        set_m = 0;
    }

    base(state_t stato){
        minuti=0;
        ora=0;
        state=stato;
        set_h = 0;
        set_m = 0;
    }

    base(state_t s,uint8_t h,uint8_t m, uint8_t s_h, uint8_t s_m, alarm_state_t on){
        ora=h;
        minuti=m;
        state=s;
        set_h = s_h;
        set_m = s_m;
        alarm_on = on;
    }

}base;

int8_t * serialize(base b);
base * deserialize(uint8_t *);


#endif
