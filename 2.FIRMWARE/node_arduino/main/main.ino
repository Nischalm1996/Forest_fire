#include "Arduino.h"
#include "LORA.h"
#include "gps.h"
#include "PIR.h"
#include "dht11.h"
#include "MQ2.h"
#include "dht11.h"

Location locationObj;
LORA transmit;
firePIR motion;
MQ2 smoke;
dhtClass temper;
boolean pir;
int mq2;
void setup()
{ Serial.begin(9600);
  Serial.println("Setup");
  locationObj.begin();
  Serial.println("location begin");

  smoke.begin();
  motion.begin(7);
  Serial.println("smoke motion begin");
  transmit.beginSender();
  //transmit.sendMessage(2, "Hi Base");
  Serial.begin(9600);
  Serial.print("Setup Done");

}
long count = 0;
void loop()
{
  locationObj.getCoordinates();
  temper.updateTemp();

  if (count >= 100)
  {

    Serial.print("humidity:");
    Serial.println(humid);
    Serial.print("temperature:");
    Serial.println(temp);
    Serial.print("PIR:");
    Serial.println(digitalRead(pirPin));
    Serial.print("MQ2:");

    Serial.println(digitalRead(MQ2Pin));
    
    Serial.print(Lat, 2);
    Serial.print(",");
    Serial.println(Lon, 2);
    String mess = "1," + (String) Lat + ' ' + (String) Lon ;
    transmit.sendMessage(2, mess);
    count = 0;
  }
  count ++;
}
