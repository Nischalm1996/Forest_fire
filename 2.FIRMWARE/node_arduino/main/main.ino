///*module to verify all the sesnors
//1. begin() --to put in setup
//2. checkingOnce()
//3. checkForFire()
//*/
//
//#ifndef _sensorCheck_H
//#define _sensorCheck_H
//#include "Arduino.h"
//#include "LORA.h"
//#include "gps.h"
//#include "PIR.h"
//#include "dht11.h"
//#include "MQ2.h"
//#include "dht11.h"
//
//LORA transmit;
//
//Location cordinates;
//PIR motion;
//MQ2 smoke;
//dht11 temper;
//boolean pir;
//int mq2;
//
//
//
//class sensorCheck
//{
//public:
//    void begin()
//    {
//        Serial.begin(9600);
//        motion.begin();
//        smoke.begin();
//        transmit.begin();
//        cordinates.begin();
//        temper.begin();
//    }
//      void checkingOnce()
//      {
//          motion.detect();
//          smoke.getMq2Value();
//          cordinates.getCoordinates();
//          transmit.sendMessage();
//          temper.readTemperature();
//     }
//      void checkForFire()
//      {
//          if(motion>500)
//          {
//              if (smoke>700)
//              {
//                if(temper>300)
//                {
//                  transmit.sendMessage(2,);
//                }
//              }
//
//          }
//      }
//      #endif //_sensorCheck_H

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
{
  Serial.begin(9600);
  locationObj.begin();
  Serial.begin(9600);
  smoke.begin();
  motion.begin(7);
  transmit.begin();
  locationObj.begin();
  transmit.sendMessage(2,"hai");
  digitalWrite(13, HIGH);   
  delay(1000);                       
  digitalWrite(13, LOW);    
  delay(1000); 
}
void loop()
{
  temper.updateTemp();
  locationObj.getCoordinates();
  
  Serial.print("humidity:");
  Serial.println(humid);
  Serial.print("temperature:");
  Serial.println(temp);
  Serial.print("MQ2:");
  Serial.println(digitalRead(MQ2Pin));
  Serial.print("motion:");
  Serial.println(digitalRead(pirPin));
  Serial.print(Lat, 6);
  Serial.print(",");
  Serial.println(Lon, 6);
  
  delay(3000);
  
  
}
