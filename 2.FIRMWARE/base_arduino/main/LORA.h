/*module to handle lora communications
  1. begin() --to put in setup
  2. sendMessage()
  3. receiveMessage()
*/

#ifndef _LORA_H
#define _LORA_H
#include "Arduino.h"
#include <String.h>
#include <SPI.h>
#include <LoRa.h>

const int8_t ss = 10;
const int8_t reset = 9;
const int8_t dio0 = 2;
char *Mess = "";

class LORA
{
  public:
   
    void beginReceiver()
    {
      Serial.begin(9600);
      LoRa.setPins(ss, reset, dio0);

      //Serial.println("LoRa Sender");

      while (!LoRa.begin(433E6))
      {
        Serial.println("Starting LoRa failed!");
        while (1);
      }
      LoRa.receive();

    }

    void receiveMessage()
    {
      String mess = "";
      // try to parse packet
      int packetSize = LoRa.parsePacket();
      if (packetSize)
      {
        while (LoRa.available())
        {
          mess = mess + (char)LoRa.read();

        }
        //Serial.println(mess);
        mess.toCharArray(Mess,(mess.length()+1));
      }
      //return (Mess);
    }
};

#endif //LORA_H
