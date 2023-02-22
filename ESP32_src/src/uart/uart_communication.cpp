#include "uart_communication.hpp"

#define TX_PIN 13
#define RX_PIN 14

volatile int8_t global_uart_rx_data = NO_DATA;

void uart_init() {
    Serial2.begin(
        9600, 
        SERIAL_8N1, 
        RX_PIN, // RX                   (RV: TX)
        TX_PIN, // TX                   (RV: RX)
        false
    );
    Serial2.onReceive(uart_on_receive);
}

void uart_on_receive(){
    global_uart_rx_data = Serial2.read();
}

/*
    Parameters:
    - recv_buf: received data buffer, where the received data will be saved
    - buf_size: the size of recv_buffer
    - act_recv: pointer to an integer value, it will be increased whenever a correct element is received
*/
void uart_receive(uint8_t* recv_buf, size_t buf_size, uint8_t* act_recv) {
    int8_t act_int, CRC;
    bool sent_crc = false;
    *act_recv = 0;

    while(*act_recv <= ( buf_size + 1 ) ) {

        // Read a value from UART, saved in buffer[act_recv] and in local variable act_int
        do{
            act_int = (int8_t) global_uart_rx_data;
        }while(act_int == NO_DATA);
        global_uart_rx_data = NO_DATA;

        DEBUG.printf("\n");
        if(Serial2.available() > 0) {
            DEBUG.printf("Found serial available!! %d\n", Serial2.available());
        }
        while(Serial2.available() > 0) {
            DEBUG.printf("thrown away %d\n", Serial2.read());
        }
        if(Serial2.available() > 0)
            DEBUG.printf("Serial > 0 after flush!\n", Serial2.available());

        if( *act_recv < buf_size )
            recv_buf[*act_recv] = act_int;

        delay(10); // Just to be sure the data is received

        //dbg
        if( act_int == ERROR_NUM )
            DEBUG.printf("a_r: %d , act_int: ERROR_NUM , [", *act_recv);
        else
            DEBUG.printf("a_r: %d , act_int: %d , [", *act_recv, act_int);
        for(int j=0;j<buf_size;j++) DEBUG.printf("%d ", recv_buf[j]);
        DEBUG.printf("]\n");

        // I'm expecting a CRC. If it's not there, this is an error
        if( *act_recv == buf_size ){
            if ( act_int != CRC_START){
                DEBUG.printf("Expected CRC_START, found %d\n", act_int);
                // recv_buf is not modified because:
                //   *act_recv is equal to lenght
                //   It's an ERROR_NUM anyway
                act_int = ERROR_NUM;
            }
        }

        switch(act_int) {
            // One of the main reserved value is ERROR_NUM, that must be negative, and is used to 
            // reset the acv_recv. Receiving data from the very beginning
            case COM_ACK:
                if( sent_crc ) {
                    DEBUG.printf("ACK received! Alright, connection closed \n");
                    // ACK received, the connection is closed
                    ( *act_recv )++;
                    break;
                } // else, there is an error! proceed sending an error_ack

            case CRC_START:
                if( *act_recv == buf_size && !sent_crc){
                    DEBUG.printf("STARTED 4-way handshake"); //dbg

                    CRC = calcCRC(recv_buf, buf_size);
                    Serial2.write((int8_t) CRC );
                    DEBUG.printf(" CRC: %d\n", CRC); //dbg

                    (*act_recv)++;
                    sent_crc = true;
                    break;
                } // else, there is an error! proceeding sending error_ack

            case ERROR_NUM:
                // The actual reset of the index
                *act_recv = 0;

                // If the CRC is wrong, we end up here. And if the sent_crc
                // variable is not reset, the second time the CRC will never be
                // sent
                sent_crc = false;

                DEBUG.println("act_recv -> ERROR_ACK");// dbg

                // Communicating to the sender that the buffer is cleared, by ERROR_ACK
                Serial2.write((int8_t) ERROR_ACK);
                break;
            case NO_DATA:
                DEBUG.println("Valutando un NO_DATA, qualcosa è andato storto nei check precedenti");
                    return;
                break;
            case ERROR_ACK:
                DEBUG.println("Il sender sta comunicando ERROR ACK, qui qualcosa è andato storto!");
                    return;
                break;
            case ZERO_NUMBER:
                // Ricevuto lo zero number, ripristino il suo valore originale
                recv_buf[*act_recv] = 0;
                act_int = 0;
            default:
                

                // Write the actual buffer index back to the sender, as descrived in protocol
                if( (*act_recv) == 0){
                    DEBUG.printf("act_recv -> %d (Thats ZERO_NUMBER)\n", ZERO_NUMBER);// dbg
                    Serial2.write((int8_t) ZERO_NUMBER);
                }else{
                    DEBUG.printf("act_recv -> %d\n", *act_recv);// dbg
                    Serial2.write((int8_t) *act_recv);
                }

                // Move the buffer index further, 
                (*act_recv)++;
        }
        Serial2.flush();
    }
}

void uart_send(int8_t * send_buf, size_t len_toSend) {
    int8_t tx_pos, local_rx_data;
    bool uart_last_error;
    uint16_t count;

    while(tx_pos < len_toSend)
    {
        if(uart_last_error == true){
            Serial2.write((uint8_t) ERROR_NUM);
            DEBUG.printf("Sent ERROR NUM\n");
        } else {
            switch(send_buf[tx_pos]){
                case 0:
                    Serial2.write((uint8_t) ZERO_NUMBER);

                    DEBUG.printf("Sent %d, thats ZERO_NUMBER\n", ZERO_NUMBER);
                    break;
                default:
                    Serial2.write(send_buf[tx_pos]);
                    DEBUG.printf("Sent %d\n", send_buf[tx_pos]);
                    break;
            }
        }

        count = 0;
        do{
            local_rx_data = (int8_t) global_uart_rx_data;
            delay(1);
            if(++count == 1000)
                local_rx_data = TIMEOUT;

        }while(local_rx_data == NO_DATA);
        global_uart_rx_data = NO_DATA;
        DEBUG.printf("Received %d\n", local_rx_data);

        delay(100);

        switch(local_rx_data) {
            case TIMEOUT:
                break;
            case ERROR_NUM:
                // This is the master. The slave cannot tell if there is a communication
                // error or not, there is a big problem if this is the case
                uart_last_error = true;
                break;
            case NO_DATA:
                // This is a placeholder for no data. There is a big problem if this is
                // the case
                uart_last_error = true;
                break;
            case ERROR_ACK:
                // Receiver just recovered from an error. Reset our buffer and start sending
                // data normally
                uart_last_error = false;
                tx_pos = 0;
                break;
            case 0:
                // Big problem. Some checks are not working
                uart_last_error = true;
                break;
            case ZERO_NUMBER:
                local_rx_data = 0;

            default:
                if( local_rx_data == tx_pos ) {
                    // Everything working. One char is sent successfully
                    tx_pos += 1;
                } else {
                    // Communication error. We will send ERROR_NUM at the next data send
                    uart_last_error = true;
                }
        }
    }
}

inline int8_t calcCRC(int8_t * buf, size_t buf_size) {

    uint32_t buf_sum = 0, i;

    for(i=0;i<buf_size;i++) {
        buf_sum += buf[i];
    }
    
    return CRC_START - ( buf_sum % CRC_SIZE );
}

inline int8_t calcCRC(uint8_t * buf, size_t buf_size) {
    
    uint32_t buf_sum = 0, i;

    for(i=0;i<buf_size;i++) {
        buf_sum += (int8_t) buf[i];
    }

    return (int8_t)CRC_START - (int8_t)( buf_sum % CRC_SIZE );
}