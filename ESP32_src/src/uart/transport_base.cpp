
#include "uart/transport_base.hpp"

int8_t * serialize(base b){
    
    int8_t * ser_temp = (int8_t*)malloc(BASE_STRUCT_SIZE_SERIALIZED * sizeof(int8_t));

    ser_temp[0] = b.state;
    ser_temp[1] = b.ora;
    ser_temp[2] = b.minuti;
    ser_temp[3] = b.set_h;
    ser_temp[4] = b.set_m;
    ser_temp[5] = b.alarm_on;

    return ser_temp;
}

base * deserialize(uint8_t serialized[BASE_STRUCT_SIZE_SERIALIZED]) {
    return new base(
        (state_t) serialized[0],
        (uint8_t) serialized[1],
        (uint8_t) serialized[2],
        (uint8_t) serialized[3],
        (uint8_t) serialized[4],
        (alarm_state_t) serialized[5]
    );
}