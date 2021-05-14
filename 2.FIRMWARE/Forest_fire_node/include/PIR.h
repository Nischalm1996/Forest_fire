/*
1. begin
2. boolean detect()
*/

#ifndef _PIR_H
#define _PIR_H
#include "Arduino.h"
const int pirPin;
class PIR
{
    public:
    void begin(int pin)
    {
        pirPin = pin;
        pinMode(pin,INPUT);
    }

    boolean detect()
    {
        return(digitalRead(pirPin));
    }


};
#endif //_PIR_H