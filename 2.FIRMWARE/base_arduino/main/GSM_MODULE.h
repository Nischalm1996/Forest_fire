#ifndef _GSM_MODULE_H
#define _GSM_MODULE_H
#include "Arduino.h"
#include <SoftwareSerial.h>

#define RX 4
#define TX 3

SoftwareSerial mySerial(RX, TX);
char incomingByte;
String inputString;
class GSM_MODULE
{
  public:
    void sendMessage(String message, String number)
    {
      mySerial.begin(9600);

      delay(1000);
      Serial.println("BEGIN MESSAGE");
      mySerial.println("AT");
      Serial.println();
      Serial.println("AT");
      delay(100);
      mySerial.println("AT+CMGF=1");
      Serial.println("AT+CMGF=1");
      delay(100);
      mySerial.println("AT+CMGS=\"" + number + "\"\r");
      Serial.println("AT+CMGS=\"" + number + "\"\r");
      delay(100);
      mySerial.print(message);
      Serial.println("message");
      mySerial.write(26);
      //Serial.write(26);
      delay(1000);

    }
};

#endif //_GSM_MODULE_H
