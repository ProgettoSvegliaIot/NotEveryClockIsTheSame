#include "webConnection.h"

void WifiConnection(){

    const char *ssid = "PiruPiru";
    const char *password = "3mesienonsentirli";
    const char *host = "esp32s3";
    EventGroupHandle_t handleServer;

    handleServer = xEventGroupCreate();
    DBG_OUTPUT_PORT.begin(115200);
    DBG_OUTPUT_PORT.setDebugOutput(true);
    DBG_OUTPUT_PORT.print("\n");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    DBG_OUTPUT_PORT.print("Connecting to ");
    DBG_OUTPUT_PORT.println(ssid);

    // Wait for connection
    uint8_t i = 0;
    while (WiFi.status() != WL_CONNECTED && i++ < 20)
    { // wait 10 seconds
        delay(500);
    }
    if (i == 21)
    {
        DBG_OUTPUT_PORT.print("Could not connect to");
        DBG_OUTPUT_PORT.println(ssid);
        while (1)
        {
            delay(500);
        }
    }
    DBG_OUTPUT_PORT.print("Connected! IP address: ");
    DBG_OUTPUT_PORT.println(WiFi.localIP());
}

void findWord(char * stringa, int * index, char * word){

        while((stringa[*index]=='{' || stringa[*index]=='}' || stringa[*index]=='"' || stringa[*index]==':' || stringa[*index]==',' || stringa[*index]=='[' || stringa[*index]==']') && stringa[*index]!='\0'){
            (*index)++;
        }

        if(stringa[*index]=='\0') { (*index) = -1; return; }


        int j=0;

        while(stringa[*index]!='{' && stringa[*index]!='}' && stringa[*index]!='"' && stringa[*index]!=':' && stringa[*index]!=',' && stringa[*index]!='[' && stringa[*index]!=']'){
            word[j++]=stringa[*index];
            (*index)++;
        }

        word[j] = '\0';
        
}

void makeParseWeather(char * stringa, Weather * w){

    char word[20] = " ";
    int l = 0; 

    while(l != -1){

        findWord(stringa, &l, word);
        printf("%s\n", word);

        if(l==-1) return;

        if(stringCmp(word,"weather"))
        { 
            int k=0;
            findWord(stringa, &l, word);
            
            while(k<4){

                if(stringCmp(word, "id")){
                    findWord(stringa, &l, word);
                    w->weather_id = atoi(word);    
                }

                else if(stringCmp(word, "main")){
                    findWord(stringa, &l, word);
                    cpy(w->weather_main, word);
                }

                else if(stringCmp(word, "description")){
                    findWord(stringa, &l, word);
                    cpy(w->weather_description, word);
                }
                else findWord(stringa, &l, word);
                findWord(stringa, &l, word);
                k++;

            }
        }        


        if(stringCmp(word, "temp")){
            findWord(stringa, &l, word);
            w->temperature = atoi(word)-273;
        } 

        if(stringCmp(word, "humidity")){
            findWord(stringa, &l, word);
            cpy(w->humidity, word);
        } 

        if(stringCmp(word, "clouds")){
            findWord(stringa, &l, word);
            findWord(stringa, &l, word);
            cpy(w->clouds, word);
        }

        if(stringCmp(word, "name")){
            findWord(stringa, &l, word);
            cpy(w->place, word);
        }

    }


}

void makeParseTransport(char * stringa, Trip * t){

    t->n_down = 0;
    t->n_up=0;
    int n_direction=0;
    bool down = false, up = false;
    char word[20] = " ";
    int l = 0; 

    while(l != -1){

        findWord(stringa, &l, word);
        printf("%s\n", word);

        if(l==-1) return;


        if(stringCmp(word, "sN")){
            findWord(stringa, &l, word);
            cpy(t->stopName, word);
        }

        if(stringCmp(word, "na")){
            if(n_direction==0){
                n_direction++;
                down = true;
                findWord(stringa, &l, word);
                cpy(t->destinationDownName, word);
            }
            else if(n_direction==1){
                down = false; 
                up = true;
                findWord(stringa, &l, word);
                cpy(t->destinationUpName, word);
            }
        }


        if(stringCmp(word, "m") && down==true){
            findWord(stringa, &l, word);
            t->busDown[t->n_down++] = atoi(word);
            if(t->n_down==3) down = false; 
        }  

        if(stringCmp(word, "m") && up==true){ 
            findWord(stringa, &l, word);
          
            t->busUp[t->n_up++] = atoi(word);
            if(t->n_up==3) up = false; 
        } 
                
    }


}

uint32_t getTimeStamp(char * stringa){

    int timeS;
    char word[20] = " ";
    int l=0;

    while(l!=-1){

        findWord(stringa, &l, word);

        if(stringCmp(word, "timestamp")){
            findWord(stringa, &l, word);
            return atoi(word);
        }      
    }

    return timeS;
}

bool weatherAPIconnection(WiFiClient & client, Weather * w){
    
    client.stop(); // close connection before sending a new request
    HTTPClient http;
    {
        String host = "api.openweathermap.org";
        String uri = "/data/2.5/weather?lat=46.06&lon=11.13&appid=a41e119935cd941552a84081c0190335";
        http.begin(client, host, 80, uri);  //HTTPS example connection
    }
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
        
        char stringa[1000] = " ";

        {
            auto coso = http.getString();
            cpy(stringa, (coso).c_str());
        }

        Serial.printf("%s\n", stringa);
        
        makeParseWeather(stringa, w); //Put data from stringa to struct

        client.stop();
        http.end();
        return true;
    }
    else
    {
        Serial.printf("connection failed, error: %s", http.errorToString(httpCode).c_str());
        client.stop();
        http.end();
        return false;
    }
    http.end();
    return true;

}

bool transportAPIconnection(WiFiClient & client, Trip * t){

    client.stop(); // close connection before sending a new request
    HTTPClient http;
    {
        String host = TT_SERVER_ADDRESS;
        String uri = "/api/stops/valoni";
        http.begin(client, host, 80, uri); //http.begin(uri,test_root_ca); //HTTPS example connection
    }
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
        
        char stringa[1000] = " ";

        {
            auto coso = http.getString();
            cpy(stringa, (coso).c_str());
        }

        Serial.printf("%s\n", stringa);
        
        makeParseTransport(stringa, t); //Put data from stringa to struct

        client.stop();
        http.end();
        return true;
    }
    else
    {
        Serial.printf("connection failed, error: %s", http.errorToString(httpCode).c_str());
        client.stop();
        http.end();
        return false;
    }
    http.end();
    return true;
}

void timestampAPIconnection(uint32_t * tStamp){

    configTime(3600, 3600, "europe.pool.ntp.org"); 

    struct tm timeinfo;
    while(!getLocalTime(&timeinfo) ) {
        Serial.println("Error getting time, retry soon");
        delay(1000);
    }

    *tStamp = mktime(&timeinfo);
}