/*
1. begin
2. int getMq2Value()
*/

#ifndef _MQ2_H
#define _MQ2_H
#include "Arduino.h"

const byte MQ2Pin = A0;

class MQ2
{
    public:
    int getMq2Value()
    {
        return(analogRead(MQ2Pin));
    }
};
#endif //_MQ2_H