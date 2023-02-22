#ifndef __WEBCONNECTION_H__
#define __WEBCONNECTION_H__

#include "utils.hpp"
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

#define DBG_OUTPUT_PORT Serial
#define TT_SERVER_ADDRESS "tqp.zanonmarco.it"
#define TIMESTAMP_SERVER_ADDRESS "api.timezonedb.com"

typedef struct Weather  //Struct for weather 
{
    char  weather_main[50];
    char  weather_description[50];
    int  temperature;
    char  humidity[5];
    char  clouds[5];
    char place[20];
    int weather_id;

}Weather;


typedef struct Trip //Struct for bus
{
    char stopName[30];
    char destinationUpName[30];
    char destinationDownName[30];

    int busDown[3];
    int busUp[3];

    int n_down;
    int n_up;

    int lineNum;

}Trip; 


void WifiConnection(); //Main function to connect to the web                                            
void makeParseWeather(char * stringa, Weather * w); //Parse string and put data in the weather struct    
void makeParseTransport(char * stringa, Trip * t); //Parse string and put data in the bus struct        
void findWord(char * stringa, int index, char * word); //Divide the string into words                   
uint32_t getTimeStamp(char * stringa); //Parse string and return timestamp                              
bool transportAPIconnection(WiFiClient & client, Trip * t); //Get data from Trentino Trasporti API      
bool weatherAPIconnection(WiFiClient & client, Weather * w); //Get data from Weather API
void timestampAPIconnection(uint32_t * tStamp); //Get data from timestamp API

#endif