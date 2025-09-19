/*! \file ota.cpp */
#include <ElegantOTA.h>
#include <Preferences.h>
#include <LiquidCrystal.h>
#include "ota.h"
#include "cStatusLed.h"

//extern LiquidCrystal lcd;
extern Preferences preferences;


//#include <WiFi.h>
//#include <WebServer.h>
//#include <WiFiClient.h>

/** Creates a webserver for OTA updates
 *  Updates must be done from URL http://[IP]/update
 *  This feature may be disable on defines.h
 *  by commenting the define ENABLE_OTA
 *  to save flash memory
 *  Wifi SSID and password are defined in
 *  platformio.ini as SSID_NAME and SSID_PASWORD
*/

extern cStatusLed  gLed;

WebServer server(80);

char fullpage[4096];

const char *welcome_msg =    
    "<!DOCTYPE html><html><head></head>"
    "<body><p style=\"text-align: center;\">"
    "<H1><center>Mind your own business!</center></H1></p>"
    "<p style=\"text-align: center;\">"
    "I don't wanna talk to you no more, you empty-headed animal food-trough wiper!<br>"
    "I fart in your general direction!<br>"
    "Your mother was a hamster and your father smelt of elderberries!<br>"
    "Now go away, or I shall taunt you a second time!"
    "</p></body></html>";


const char *header_2 =    
    "<!DOCTYPE html><html><head></head>"
    "<body><p style=\"text-align: center;\">"
    "<H1><center>LOGS</center></H1></p>";
    




void ota_setup(){
}

void add_text(char *_text, const char *_toadd)
{
    strcpy(&_text[strlen(_text)], _toadd);
}


void ota_loop()
{
    static wl_status_t old_status = WL_DISCONNECTED;

    wl_status_t newstatus = WiFi.status();

    if(newstatus != old_status)
    {
        if(newstatus == WL_CONNECTED)
        {
            gLed.SetState(LED_STATUS_ONLINE);

            Serial.println("");
            Serial.print("Connected to ");
            Serial.println(SSID_NAME);
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());

            server.on("/", []() 
            {
                server.send(200, "text/html", welcome_msg );
            });

            ElegantOTA.begin(&server);    // Start ElegantOTA
            server.begin();
            Serial.println("HTTP server started");

        }
        old_status = newstatus;
        server.on("/", []() 
        {
            server.send(200, "text/html", welcome_msg );
        });
    }

    if(newstatus == WL_CONNECTED)
        server.handleClient();
}