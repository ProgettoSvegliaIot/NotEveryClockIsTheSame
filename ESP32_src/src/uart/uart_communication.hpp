#pragma once

#include "cstring"
#include <Arduino.h>
#include <esp32-hal-uart.h>

#define DEBUG Serial

/* Static variables between the two cards */
#define ERROR_NUM 125
#define ZERO_NUMBER 127
#define NO_DATA 126
#define ERROR_ACK 124
#define COM_ACK 123
#define TIMEOUT 122
#define CRC_START 121
#define CRC_SIZE 55

#define recv_all(len) (act_recv == len)

void uart_init();
void uart_receive(uint8_t* recv, size_t, uint8_t* act_recv);
void uart_send(int8_t * send_buf, size_t len_toSend);

inline int8_t calcCRC(uint8_t * buf, size_t buf_size);
inline int8_t calcCRC(int8_t * buf, size_t buf_size);

void uart_on_receive();
