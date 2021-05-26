/*
1. begin
2. boolean detect()
*/

#ifndef _PIR_H
#define _PIR_H
#include "Arduino.h"
int pirPin;
class firePIR
{
    public:
    void begin(int pin)
    {
        pirPin = pin;
        pinMode(pirPin,INPUT);
    }

    boolean detect()
    {
        return(digitalRead(pirPin));
    }


};
#endif //_PIR_H
