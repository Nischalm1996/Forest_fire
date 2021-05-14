#include <Arduino.h>
#include "sensorCheck.h"

sensorCheck fire;
void setup()
{
   put your setup code here, to run once:
  fire.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
  fire.checkingOnce();
  fire.checkForFire();
}