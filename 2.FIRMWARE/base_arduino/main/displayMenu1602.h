#ifndef _DISPLAY_MENU_1602_H
#define _DISPLAY_MENU_1602_H
#include "Arduino.h"
#include <Wire.h>
// The I2C LCD library
#include <LiquidCrystal_I2C.h>
// The menu wrapper library
#include <LiquidMenu.h>
#include "GSM_MODULE.h"
#include "Button.h"
#include "LORA.h"
GSM_MODULE gsmObj;
// Button objects instantiation
const bool pullup = true;
Button left(6, pullup, 200);
Button right(7, pullup, 200);
Button enter(5, pullup, 200);

////loara obj
LORA comm;
String PHONE = "+916362410309";
char * cord;
char * Temp = "0.0" ;
LiquidCrystal_I2C lcd(0x27, 16, 2);
LiquidLine welcome_line1(1, 0, "FOREST FIRE DET");
LiquidLine welcome_line2(1, 1, "BASE STATION");

LiquidLine welcome_line3(1, 0, "NODES ACTIVE!");
LiquidLine welcome_line4(1, 1, "NO FIRE EVENT!");

LiquidLine FIRESCREEN11(1, 0, "FIRE IN NODE 1! ");
LiquidLine FIRESCREEN12(1, 1, cord );
LiquidLine FIRESCREEN13(1, 0, "FIRE IN NODE 2!");
LiquidLine messageLine(1, 1, " MESSAGE SENT!");
LiquidLine tempLine(1, 0, "Temp:", Temp);

LiquidScreen welcome_screen(welcome_line1, welcome_line2);
LiquidScreen normalScreen(welcome_line3, welcome_line4);

LiquidScreen FIRENODE1(FIRESCREEN11, FIRESCREEN12);
LiquidScreen FIRENODE2(FIRESCREEN13, FIRESCREEN12);
LiquidScreen MESSAGE(tempLine, messageLine);

LiquidMenu menu(lcd);
int count = 0;
class displayMenu1602
{

  public:
    void begin()
    {

      Serial.begin(9600);

      // This is the I2C LCD object initialization.
      lcd.init();
      lcd.backlight();
      delay(500);
      lcd.noBacklight();
      delay(500);
      lcd.backlight();

      // Menu initialization.
      menu.init();
      // This is the method used to add a screen object to the menu.
      menu.add_screen(welcome_screen);
      menu.add_screen(normalScreen);

      menu.add_screen(FIRENODE1);
      menu.add_screen(FIRENODE2);
      menu.add_screen(MESSAGE);
      comm.beginReceiver();
      menu.update();
      delay(3000);
      if (menu.get_currentScreen() == &welcome_screen) {
        menu.change_screen(&normalScreen);
        menu.update();
      }

      //gsmObj.sendMessage("BASE BEGIN", PHONE);

    }
    void runMenu()
    {
      // Check all the buttons
      if (right.check() == LOW)
      {
        Serial.println(F("RIGHT button pressed"));
        menu.next_screen();
      }
      if (left.check() == LOW)
      {
        Serial.println(F("LEFT button pressed"));
        menu.previous_screen();
      }
      if (enter.check() == LOW)
      {
        // Switches focus to the next line.
        Serial.println(F("OK button pressed"));
        menu.switch_focus();
      }
      if (menu.get_currentScreen() == &welcome_screen) {
        menu.change_screen(&normalScreen);
        menu.update();
      }
      if (count >= 30000)
      {
        count = 0;
        menu.update();
        Serial.print("loop:");
        Serial.println(Mess);
      }

      comm.receiveMessage();
      count++;
      DetectFromNode();
    }
    void DetectFromNode()
    {
      String dataIn = (String)Mess;
      int indexofS = dataIn.indexOf("S");
      int indexofX = dataIn.indexOf("X");
      int indexofA = dataIn.indexOf("A");
      int indexofB = dataIn.indexOf("B");
      int indexofC = dataIn.indexOf("C");

      String Node = dataIn.substring (indexofS + 1 , indexofA);
      String Lat = dataIn.substring (indexofA + 1 , indexofB);
      String Lon = dataIn.substring (indexofB + 1 , indexofC);
      String temp = dataIn.substring (indexofC + 1 , indexofX);

      String Message = "Fire Det!\n" + Node + "\nCord:" + Lat + "," + Lon + "\n" + temp;
      Temp = &temp[0];
      String cordinates = Lat + ',' +  Lon;
      cord = &cordinates[0];

      if (Node.equals("1"))
      {
        //Display Fire and GPS Also Send Message
        Serial.println(Message);
        gsmObj.sendMessage(Message, PHONE);
        delay(200);
        for (int i = 0; i < 4; i++)
        {
          menu.change_screen(&FIRENODE1);
          delay(2000);
          menu.change_screen(&MESSAGE);
          delay(2000);
        }
        Node = "";
        menu.change_screen(&normalScreen);

      }
      if (Node.equals("2"))
      {
        //Display Fire At Node 2 and GPS
        Serial.println(Message);
        gsmObj.sendMessage(Message, PHONE);
        delay(200);

        for (int i = 0; i < 4; i++)
        {
          menu.change_screen(&FIRENODE2);
          delay(2000);
          menu.change_screen(&MESSAGE);
          delay(2000);

        }
        menu.change_screen(&normalScreen);

        Node = "";
      }

    }
};


#endif //_DISPLAY_MENU_1602_H
