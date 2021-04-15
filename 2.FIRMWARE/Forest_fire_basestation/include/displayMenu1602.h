#ifndef _DISPLAY_MENU_1602_H
#define _DISPLAY_MENU_1602_H
#include "Arduino.h"
#include <Wire.h>
// The I2C LCD library
#include <LiquidCrystal_I2C.h>
// The menu wrapper library
#include <LiquidMenu.h>
// The I2C LCD object
#include "Button.h"
//OK  D5
//LEFT  D6
//RIGHT D7
//BACK  D8

// Button objects instantiation
const bool pullup = true;
Button left(6, pullup);
Button right(7, pullup);
//Button up(8, pullup);
//Button down(9, pullup);
Button enter(5, pullup);

LiquidCrystal_I2C lcd(0x27, 16, 2);
LiquidLine welcome_line1(1, 0, "Base-Station ");
LiquidLine welcome_line2(1, 1, "NO FIRE EVENT!");
LiquidScreen welcome_screen(welcome_line1, welcome_line2);
LiquidLine FIRESCREEN11(1, 0, "FIRE DETECTED! ");
LiquidLine FIRESCREEN12(1, 1, " IN NODE X!");
LiquidScreen FIRESCREEN1(FIRESCREEN11, FIRESCREEN12);
LiquidLine FIRESCREEN21(1, 0, "FIRE DETECTED! ");
LiquidLine FIRESCREEN22(1, 1, " MESSAGE SENT!");
LiquidScreen FIRESCREEN2(FIRESCREEN21, FIRESCREEN22);

LiquidMenu menu(lcd);

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
        menu.add_screen(FIRESCREEN1);
        menu.add_screen(FIRESCREEN2);

        menu.update();
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
            Serial.println(F("ENTER button pressed"));
            // Switches focus to the next line.

            menu.switch_focus();
        }
    }
};

#endif //_DISPLAY_MENU_1602_H