#include <Arduino.h>
#include <LiquidCrystal.h>
#include "wifi.h"
#include "cStatusLed.h"
#include "defines.h"
#include "ota.h"
#include "stepper.h"
#include "ntp.h"

#define GPIO_LED        LED_BUILTIN   //defines the IO pin for tue status LED

#define UPDATESECONDS   3  //this sets the second that will trigger the motor to spin, to match with the new minute
                           //my clock takes 3 seconds to spin the minute wheel


//!< this disables the ESP32 brownout detection. Don't use in production
//!< remove it from the platformio.ini in the final build
#ifdef DISABLE_BROWNOUT   
  #warning BROWNOUT DISABLED
 #include "soc/soc.h"
 #include "soc/rtc_cntl_reg.h"
#endif 


cStatusLed  gLed(GPIO_LED, true);

void setup(){
#ifdef DISABLE_BROWNOUT
   WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
#endif
   Serial.begin(9600);
  delay(15);
//  preferences.begin("clock", false); 
  gLed.SetState(LED_STATUS_OFFLINE);
  stepper_setup();
}

void loop() {
  bool online = wifi_loop();
  ota_task();
  
  if(online && gLed.GetState() == LED_STATUS_OFFLINE)
    gLed.SetState(LED_STATUS_ONLINE);

  if(online)
    update_time();

  gLed.Task();
  if(minute_changed(UPDATESECONDS))
    stepper_move(1536);

  stepper_loop();
}

//eof main