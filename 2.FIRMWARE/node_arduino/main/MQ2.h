/*
  1. begin
  2. int getMq2Value()
*/

#ifndef _MQ2_H
#define _MQ2_H
#include "Arduino.h"

const byte MQ2Pin = 6;

class MQ2
{
  public:
    void begin()
    {
      pinMode(MQ2Pin, INPUT);
    }
    int getMq2Value()
    {
      return (digitalRead(MQ2Pin));
    }
};
#endif //_MQ2_H
