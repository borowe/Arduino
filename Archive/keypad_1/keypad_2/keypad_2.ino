//  Program to output keypad strokes to an LCD
//  2.8.2012
//  Bob Rowe, Imagine Nation
// "[...] guided by whim, imagination and curiousity."


#include <LiquidCrystal.h>  //Include the LCD library
#include <Keypad.h>         //Include the Kepyad library


//Kepyad setup
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
int presscount = 0;

void setup(){
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad

  lcd.begin(16,2);
  lcd.blink();
  lcd.home();
  
}

void loop(){
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
  }
}

//take care of some special events
void keypadEvent(KeypadEvent key){
  char state = keypad.getState();
  
// To do when a key is pressed:  
  if (state == PRESSED){
        presscount = presscount + 1;
        lcd.print(key);
     }
     
// To do when a key is released:
  if (state == RELEASED)
  {
    if (presscount == 16){
        if (rowe == 1){
          rowe = 2;
          lcd.setCursor(1,rowe);
          presscount = 1;
        }
        else {
          lcd.clear();
          lcd.home();
          presscount = 0;
          rowe = 1;
        }
    }
    if (key == '*' ){
        lcd.clear();
        lcd.home();
    }
  }
 
 // To do when a key is held down:
    if (state == HOLD && key == '*'){
      lcd.noDisplay();
    }
    else{
      lcd.display();
    }
}
