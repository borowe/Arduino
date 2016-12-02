//  Program to accept temperature inputs from keypad
//  4.16.2012
//  ImagineN4tion
// "[...] guided by Whim, imagination and curiousity."


#include <LiquidCrystal.h>  //Include the LCD library
#include <Keypad.h>         //Include the Kepyad library

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {7, 5, 4, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, A4, A5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

int cole = 1;
int rowe = 1;


void setup(){
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}

void loop(){
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
  }
}

//take care of some special events
void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    
    case PRESSED:
//      switch (key){
//        case '#': lcd.print("you pressed #"); break;
        lcd.print(key); 
//        break; 
//      }
    break;
    
    case RELEASED:
//      switch (key){
        case '*': lcd.clear();
        break;
        case'1,2,3,4,5,6,7,8,9,0,#':
          lcd.setCursor(cole,rowe);
          cole = cole + 1;
          if (cole == 17){
            cole = 1;
            rowe = rowe  + 1;
          }
        break;
//      }
    break;
    
//    case HOLD:
//      switch (key){
//        case '*': lcd.print("stop holding"); break;
//      }
//    break;
  }
}

