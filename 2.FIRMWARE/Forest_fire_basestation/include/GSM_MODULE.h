#ifndef _GSM_MODULE_H
#define _GSM_MODULE_H
#include "Arduino.h"
#include <SoftwareSerial.h>
#include "LED.h"

#define RX 4
#define TX 3

SoftwareSerial mySerial(RX, TX);
char incomingByte;
String inputString;

Led led(10);
boolean LASER_CONTROL = false;
class GSM_MODULE
{
public:
    void sendMessage(String message, String number)
    {
        mySerial.begin(9600);
        delay(1000);
        mySerial.println("AT");
        delay(500);
        mySerial.println("AT+CMGF=1");
        delay(500);
        mySerial.println("AT+CMGS=\"" + number + "\"\r");
        delay(500);
        mySerial.print(message);
        delay(500);
        mySerial.write(26);
        delay(1000);
    }
    void beginReadSMS()
    {
        mySerial.begin(9600);
        while (!mySerial.available())
        {
            mySerial.println("AT");
            delay(1000);
            // Serial.println("Connecting...");
        }
        //Serial.println("Connected!");
        mySerial.println("AT+CMGF=1"); //Set SMS to Text Mode
        delay(1000);
        mySerial.println("AT+CNMI=1,2,0,0,0"); //Procedure to handle newly arrived messages(command name in text: new message indications to TE)
        delay(1000);
        mySerial.println("AT+CMGL=\"REC UNREAD\""); // Read Unread Messages
        delay(500);
    }
    void readSMSAndAct()
    {
        if (mySerial.available())
        {
            delay(100);

            // Serial Buffer
            while (mySerial.available())
            {
                incomingByte = mySerial.read();
                inputString += incomingByte;
            }

            delay(10);

            inputString.toUpperCase(); // Uppercase the Received Message
            Serial.println(inputString);

            //turn RELAY ON or OFF
            if (inputString.indexOf("ON") > -1)
            {
                digitalWrite(13, HIGH);
                LASER_CONTROL = true;
                Serial.println("ON");
            }
            if (inputString.indexOf("OFF") > -1)
            {
                digitalWrite(13, LOW);
                LASER_CONTROL = false;
                Serial.println("OFF");
            }

            delay(50);

            //Delete Messages & Save Memory
            if (inputString.indexOf("OK") == -1)
            {
                mySerial.println("AT+CMGDA=\"DEL ALL\"");

                delay(1000);
            }

            inputString = "";
        }
    }
};

#endif //_GSM_MODULE_H