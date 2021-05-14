/*module to verify all the sesnors
1. begin() --to put in setup
2. checkingOnce()
3. checkForFire()
*/

#ifndef _sensorCheck_H
#define _sensorCheck_H
#include "Arduino.h"
#include <LoRa.h>
#include <gps.h>
#include <PIR.h>
#include <DHT11.h>
#include <MQ2.h>
#include <DHT11.h>

LORA transmit;
GPS cordinates;
PIR motion;
MQ2 smoke;
dht11 temper;


class sensorCheck
{
public:
    void begin()
    {
        Serial.begin(9600);
        motion.begin();
        smoke.begin();
        transmit.begin();
        cordinates.begin();
    }
      void checkingOnce()
      {
          motion.detect();
          smoke.getMq2Value();
          cordinates.updateCoordinates();
          transmit.sendMessage();
          temper.readTemperature();
     }
      void checkForFire()
      {
          if(motion>500)
          {
              if (smoke>700)
              {
                if(temper>300)
                {
                  transmit.sendMessage();
                }
              }
              
          }
      }
      #endif //_sensorCheck_H