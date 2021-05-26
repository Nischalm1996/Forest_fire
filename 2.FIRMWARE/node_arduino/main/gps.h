#ifndef _GPS_H
#define _GPS_H
#include "Arduino.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>


double Lat = 0, Lon = 0;
// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial serialobj(3, 4);
class Location
{
  public:
    void begin()
    {
      serialobj.begin(9600);
    }

    void getCoordinates()
    {
      while (serialobj.available() > 0) {
        byte gpsData = serialobj.read();
        gps.encode(serialobj.read());
        if (gps.location.isUpdated()) {
          //Serial.print("Latitude= ");
          Lat = gps.location.lat();
          //Serial.print(" Longitude= ");
          Lon = gps.location.lng();
        }
      }
    }
};
#endif //_gps_H
