#include <Arduino.h>
#include "ledLib.hpp"

void ledInit(){
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

bool ledBlinker(int interval){
  static unsigned long lastTime=0;
  static bool ledState=false;

  if(millis()-lastTime>=interval){
    lastTime=millis();
    ledState=!ledState;
    digitalWrite(LED_BUILTIN, ledState);
    return true;
  }
  return false;
}
