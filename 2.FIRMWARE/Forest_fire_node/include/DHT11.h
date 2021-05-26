/* program for dht11 sensor.
1. begin()  initialise variables
2. void updateTemp()
3. float temp=temperature value 
4. float humid= humidity value
5. float fahren= fahrenheit value*/

#define _DHT11_H

#include <dht.h>  // Include library
#define outPin 5  // Defines pin number to which the sensor is connected

dht DHT;      // Creates a DHT object
float temp = 0;
float humid = 0;
float fahren = 0;

class dhtClass
{
  public:
    void updateTemp()
    {
      DHT.read11(outPin);
      temp = DHT.temperature;
      // Serial.println(temp);
      humid = DHT.humidity;
      //Serial.println(humid);
      fahren = ((temp * 9.0) / 5.0 + 32.0);
      //Serial.println(fahren);
    }
};

#endif //_DHT11_H