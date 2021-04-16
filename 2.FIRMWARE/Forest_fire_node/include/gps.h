/*
1. begin
2. update co-ordinates
*/

#ifndef _LORA_H
#define _LORA_H
#include "Arduino.h"
#include <TinyGPS.h>

//long   lat,lon; // create variable for latitude and longitude object
float lat, lon;
TinyGPS gps; // create gps object
class GPS
{
public:
    void begin()
    {
        Serial.begin(9600); // connect gps serial
    }

    void updateCoordinates()
    {
        while (Serial.available())
        {                                  // check for gps data
            if (gps.encode(Serial.read())) // encode gps data
            {
                gps.f_get_position(&lat, &lon); // get latitude and longitude
            }
        }
    }
};

#endif //_LORA_H