/*module to handle lora communications
  1. begin() --to put in setup
  2. sendMessage()
  3. receiveMessage()
*/

#ifndef _LORA_H
#define _LORA_H
#include "Arduino.h"
#include <SPI.h>
#include <LoRa.h>

const int8_t ss = 10;
const int8_t reset = 9;
const int8_t dio0 = 2;

class LORA
{
  public:
    void begin()
    {
      Serial.begin(9600);
      while (!Serial)
        ;

      LoRa.setPins(ss, reset, dio0);

      //Serial.println("LoRa Sender");

      while(!LoRa.begin(433E6))
      {
        Serial.println("Starting LoRa failed!");
        //while (1);
        delay(1000);
      }
    }
    void sendMessage(int counter, String message)
    {
      Serial.print("Sending packet: ");
      Serial.println(counter);
      for (int i = 1; i <= counter; counter++)
      {
        // send packet
        LoRa.beginPacket();
        LoRa.print(message);
        LoRa.endPacket();
        delay(5000);
      }
    }

    String receiveMessage()
    {
      String Message = "";
      // try to parse packet
      int packetSize = LoRa.parsePacket();
      if (packetSize)
      {
        // received a packet
        Serial.print("Received packet '");

        // read packet

        while (LoRa.available())
        {
          Message = Message + (char)LoRa.read();
        }
        Serial.println(Message);

        // print RSSI of packet
        //Serial.print("' with RSSI ");
        //Serial.println(LoRa.packetRssi());
      }
      return(Message);
    }
};

#endif //LORA_H
