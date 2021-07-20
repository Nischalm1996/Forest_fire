#ifndef _GPS_H
#define _GPS_H
#include "Arduino.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>


double Lat = 0, Lon = 0;
// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial serialobj(4, 3);
class Location
{
  public:
    void begin()
    {
      serialobj.begin(9600);
    }

    void getCoordinates()
    {
      serialobj.begin(9600);
      while (serialobj.available() > 0) {
        //byte gpsData = serialobj.read();
        //Serial.print(serialobj.read());
        gps.encode(serialobj.read());
      }
      if (gps.location.isValid()) {
//        Serial.print("Latitude= ");
//        Serial.print(gps.location.lat());

        Lat = gps.location.lat();
//        Serial.print(" Longitude= ");
//        Serial.print(gps.location.lng());

        Lon = gps.location.lng();
      }
    }

};
#endif //_gps_H
