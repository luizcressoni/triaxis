#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Preferences.h>
#include <ezButton.h>
#include <time.h>
#include "wifi.h"
#include "cStatusLed.h"
#include "defines.h"
#include "ota.h"
#include "stepper.h"
#include "ntp.h"

#define GPIO_LED        LED_BUILTIN   //defines the IO pin for tue status LED

#define UPDATESECONDS   4  //this sets the second that will trigger the motor to spin, to match with the new minute
                           //my clock takes 3 seconds to spin the minute wheel


//!< this disables the ESP32 brownout detection. Don't use in production
//!< remove it from the platformio.ini in the final build
#ifdef DISABLE_BROWNOUT   
  #warning BROWNOUT DISABLED
 #include "soc/soc.h"
 #include "soc/rtc_cntl_reg.h"
#endif 


cStatusLed  gLed(GPIO_LED, true);
Preferences preferences;

ezButton button_minus(KEY_MINUS);
ezButton button_plus(KEY_PLUS);
ezButton button_advance_one(KEY_ADVANCE_ONE);

void buttons_setup(){
  button_minus.setDebounceTime(50);
  button_plus.setDebounceTime(50);
  button_advance_one.setDebounceTime(50);
}


void setup(){
#ifdef DISABLE_BROWNOUT
   WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
#endif
   Serial.begin(9600);
  delay(15);
  preferences.begin("clock", false); 
  gLed.SetState(LED_STATUS_OFFLINE);
  stepper_setup();
  buttons_setup();
}

void save_current_time()
{
  struct tm timeinfo;
    if(!getLocalTime(&timeinfo)) {
        Serial.println("Getlocaltime failed");
        return;
    }
    preferences.putInt("hour", timeinfo.tm_hour);
    preferences.putInt("min", timeinfo.tm_min);
}

uint32_t spin_to_current_time()
{
    int hour = preferences.getInt("hour");
    int minutes = preferences.getInt("min");
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)) {
        Serial.println("Getlocaltime failed");
        return 0;
    }
    //calculate time difference
    int last_minutes = ((hour % 12) * 60) + minutes;
    int now_minutes  = ((timeinfo.tm_hour % 12) * 60) + timeinfo.tm_min;
    int delta_minutes = now_minutes - last_minutes;
    if(delta_minutes < 0)
      delta_minutes += 12 * 60;
    
    return delta_minutes;
}

int test_buttons()
{
  if(button_minus.isPressed())
    return -100;
  else if(button_plus.isPressed())
    return 100;  
  else if(button_advance_one.isPressed())
    return PULSES_PER_MINUTE;  
    
  return 0;
}

void button_task()
{
  button_minus.loop();
  button_plus.loop();
  button_advance_one.loop();
}

void loop() {
  button_task();
  bool online = wifi_loop();
  ota_loop();
  
  if(online && gLed.GetState() == LED_STATUS_OFFLINE)
  {
#ifdef UPDATE_ON_START
    stepper_move(spin_to_current_time() * PULSES_PER_MINUTE);
#endif
    gLed.SetState(LED_STATUS_ONLINE);
  }

  if(online)
    update_time();

  gLed.Task();
  if(minute_changed(UPDATESECONDS)){
    save_current_time();
    stepper_move(PULSES_PER_MINUTE);
  }
  else{
    int value = test_buttons();
    if(value)
      stepper_move(value);
  }

  stepper_loop();
}

//eof main