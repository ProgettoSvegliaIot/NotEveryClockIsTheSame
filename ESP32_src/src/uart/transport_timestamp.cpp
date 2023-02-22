
#include "transport_timestamp.hpp"

void serialize_time(int32_t timestamp, int8_t * base) {

    for(int i=0;i<6;i++) {
        // uint to force logical shift and to not edit the value before saving
        base[i] = (uint8_t) ( ( (uint32_t) timestamp ) >> (6 * i) );
        base[i] <<= 2;
        // Uint to force the logical shift!
        base[i] = ((uint8_t) base[i]) >> 2;
    }


}

void deserialize_time(int8_t * serialized, int32_t * timestamp ) {
    *timestamp = (uint32_t) 0;

    for(int i=0;i<6;i++) {
        *timestamp |= ( (uint8_t) serialized[i]) << (6 * i);
    }
}