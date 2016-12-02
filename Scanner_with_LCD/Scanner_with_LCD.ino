/*  PS2Keyboard library example
  
  PS2Keyboard now requries both pins specified for begin()

  keyboard.begin(data_pin, irq_pin);
  
  Valid irq pins:
     Arduino Uno:  2, 3
     Arduino Due:  All pins, except 13 (LED)
     Arduino Mega: 2, 3, 18, 19, 20, 21
     Teensy 2.0:   All pins, except 13 (LED)
     Teensy 2.0:   5, 6, 7, 8
     Teensy 1.0:   0, 1, 2, 3, 4, 6, 7, 16
     Teensy++ 2.0: 0, 1, 2, 3, 18, 19, 36, 37
     Teensy++ 1.0: 0, 1, 2, 3, 18, 19, 36, 37
     Sanguino:     2, 10, 11
  
  for more information you can read the original wiki in arduino.cc
  at http://www.arduino.cc/playground/Main/PS2Keyboard
  or http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
  
  Like the Original library and example this is under LGPL license.
  
  Modified by Cuninganreset@gmail.com on 2010-03-22
  Modified by Paul Stoffregen <paul@pjrc.com> June 2010
*/
   
// include the library code:
#include "Wire.h"
#include <PS2Keyboard.h>
#include "LiquidCrystal.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(0);

const int DataPin = 5;
const int IRQpin =  3;

PS2Keyboard keyboard;

 char code[13];
 char beer[] = "892376002036";
 char wine[] = "088586403866";
 int codesize = 0;

void setup() {
   // set up the LCD: 
  lcd.begin(16, 2);
  //lcd.autoscroll();

  //barcode reader setup
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Keyboard Test:");
 
}

void loop() {
  

  if (keyboard.available()) {
    
    // read the next key
    char c = keyboard.read();
    
    // check for some of the special keys
    if (c == PS2_ENTER) {
      Serial.println();
    } else if (c == PS2_TAB) {
      Serial.print("[Tab]");
    } else if (c == PS2_ESC) {
      Serial.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      Serial.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      Serial.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      Serial.print("[Left]");
    } else if (c == PS2_RIGHTARROW) {
      Serial.print("[Right]");
    } else if (c == PS2_UPARROW) {
      Serial.print("[Up]");
    } else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");
    } else if (c == PS2_DELETE) {
      Serial.print("[Del]");
    } else {
      

      // otherwise, just print all normal characters
    
     // Serial.print(c);

   }
         
         
      if(c != 'j')
      {
        code[codesize] = c;
        codesize++;
      }
      else
      {
        if (*code == *beer) {
          
          Serial.print(1);
         lcd.clear();
         
         lcd.setCursor(0, 16);
         lcd.print("Ninkasa Ale");
         delay(1000);
         for(int i = 0; i < 15; i++)
         {
         lcd.scrollDisplayLeft();
         delay(300);
         }
         delay(1000);
         lcd.clear();
         lcd.setCursor(0, 16);
         lcd.print("Pairs with: Hamburgers");
         delay(500);
         for(int i = 0; i < 15; i++)
         {
         lcd.scrollDisplayLeft();
         delay(300);
         }
         delay(1000);
         lcd.clear();
         lcd.setCursor(0, 16);
         lcd.print("Similar to: Manny's Pale");
         delay(500);
         for(int i = 0; i < 15; i++)
         {
         lcd.scrollDisplayLeft();
         delay(300);
         }
         
         delay(500);
         lcd.clear();
         
         

        }
        else if (*code == *wine) {
          
          Serial.print(2);
          lcd.clear();
          
         lcd.setCursor(0, 16);
         lcd.print("Two Vines Chard");
         delay(1000);
         for(int i = 0; i < 15; i++)
         {
         lcd.scrollDisplayLeft();
         delay(300);
         }
         delay(1000);
         lcd.clear();
         lcd.setCursor(0, 16);
         lcd.print("Pairs with: Fish, Poultry");
         delay(500);
         for(int i = 0; i < 15; i++)
         {
         lcd.scrollDisplayLeft();
         delay(300);
         }
         delay(1000);
         lcd.clear();
         lcd.setCursor(0, 16);
         lcd.print("Similar to: St. Michelle Chard");
         delay(500);
         for(int i = 0; i < 15; i++)
         {
         lcd.scrollDisplayLeft();
         delay(300);
         }
         
         delay(500);
         lcd.clear();
         
         
         
         

        //lcd.clear();   
        }
        else {
         lcd.clear();
         lcd.setCursor(0, 1);
         
         lcd.print("none"); 
         Serial.print(3);
        }
        //Serial.print(code); 
       codesize = 0;
      }
     
    }
    

      
  }
  

  

