/*! \file ntp.cpp */
#include "ntp.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -3 * 3600;  // Example: GMT-3 (Brasília)
const int   daylightOffset_sec = 0;     // DST if aplicable

const unsigned long ntpUpdateInterval = 3600;  // 1 hour to update NTP time
unsigned long lastNtpUpdate = 0;


/*! \brief Initializes the NTP. Call if only if connected to WiFi */
void init_ntp() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();
    lastNtpUpdate = millis() / 1000;
}

/*! \brief Sends local time to serial port */
void printLocalTime() {
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)) {
        Serial.println("Getlocaltime failed");
        return;
    }
    Serial.printf("Hora atual: %02d:%02d:%02d - %02d/%02d/%04d\n",
                  timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec,
                  timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
}

/*! \brief Updates time from NTP server */
void update_time() {
    unsigned long now = millis() / 1000;
     if (now - lastNtpUpdate >= ntpUpdateInterval) {
        Serial.println("Updating time from NTP...");
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        printLocalTime();
        lastNtpUpdate = now;
    }
}

/*! \brief Generates a pulse when minute has changed 
    \note Set flipseconds so the clock has time to spin to match a new minute on time
    \return true if a new minute has come
*/
bool minute_changed(byte flipseconds)
{
    bool ret = false;
    static unsigned long last_update = 0;
    unsigned long now = millis();
    if(now - last_update < 1000)
        return false;
    last_update = now;
    static uint8_t min = 0;
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)) {
        Serial.println("Falha ao obter hora");
        return false;
    }
    if(min != timeinfo.tm_min && timeinfo.tm_sec >= (60 - flipseconds))
    {
        min = timeinfo.tm_min;
        ret = true;
    }
    return ret;
}

// eof ntp.cpp