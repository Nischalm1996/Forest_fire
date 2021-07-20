#ifndef _DHT11_H
#define _DHT11_H

#include "DHT.h"
#define outPin 5  // Defines pin number to which the sensor is connected
#define DHTTYPE DHT11
//dht Dht;      // Creates a DHT object
DHT Dht(outPin, DHTTYPE);
float temp = 0;
float humid = 0;
float fahren = 0;


class dhtClass
{
  public:
    void updateTemp()
    {
      Dht.begin();
      //Dht.read11(outPin);
      temp = Dht.readTemperature();
      // Serial.println(temp);
      humid = Dht.readHumidity();
      //Serial.println(humid);
      fahren = Dht.readTemperature(true);
      //Serial.println(fahren);
    }
};

#endif //_DHT11_H
