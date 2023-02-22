#ifndef TESTING_TRANSPORT_TIMESTAMP_HPP
#define TESTING_TRANSPORT_TIMESTAMP_HPP

#include <Arduino.h>

#define TIMESTAMP_SIZE_SERIALIZED 6 

void serialize_time(int32_t timestamp, int8_t * base);
void deserialize_time(int8_t * serialized, int32_t * timestamp );

#endif //TESTING_TRANSPORT_TIMESTAMP_HPP
