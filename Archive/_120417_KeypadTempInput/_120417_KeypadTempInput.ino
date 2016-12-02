//  Program to accept temperature inputs from keypad
//  4.16.2012
//  ImagineN4tion
// "[...] guided by Whim, imagination and curiousity."

//$$ Include Libraries
#include <LiquidCrystal.h>  //Include the LCD library
#include <Keypad.h>         //Include the Kepyad library


//$$ Configure the Keypad you are using, set how many rows and columns, define pins it's on, create keypad map
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



//$$ Configure the LCD by defining the pins it is connected to
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);



//$$ Setup Program Components - serial port communication, the LCD, the Keypad event listener
void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  lcd.home();
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}


//$$ Main program loop that is executed and reacts to some keypad event (aka: a key is pressed)
void loop(){
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
  }
}


// When there is a keypad event get the current state: PRESSED, RELEASED OR HOLD, and process code accordingly
void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    
    
// Depending on what key is pressed we have different courses of action.    
    case PRESSED:
      switch (key){
        
// Press # to awaken the wine cooler display.  It then prompts for a desired temperature.
        case '#':                     //Start case where # is pressed
           lcd.display();                    // Turn on LCD display
           lcd.clear();                      // Clear home
           lcd.home();                       // Return cursor to home position (upper left corner)
           lcd.print("Welcome Jillian,");    //Print some text
           delay(1000);                      // Delay for some period
           lcd.setCursor(0,1);               //Set cursor to the second Row first Column
           lcd.print("to Wine City.");       // Print some text
           delay(5000);                      //Delay for some time
           lcd.clear();                      // Clear home
           lcd.home();                       // Return cursor to home position (upper left corner)







           lcd.print("Enter Desired");       // Print some text
           delay(1000);                      //Delay for some time
           lcd.setCursor(0,1);               //Set cursor to the second Row first Column
           lcd.print("Temperature:");       // Print some text
           delay(5000);                      //Delay for some time
           lcd.clear();                      // Clear home
           lcd.home();                       // Return cursor to home position (upper left corner)
 //          lcd.blink();                      //Blink Cursor
           
           // Insert way of reading keystrokes to set temperature.
           
           
 //          lcd.clear();                      // Clear home
 //          lcd.home();                       // Return cursor to home position (upper left corner)
           

           
           
        break;                               //End case where # is pressed
        
        default:  //Start case where any other key is pressed
           lcd.display();                    // Turn on LCD display
           lcd.clear();                      // Clear home
           lcd.home();                       // Return cursor to home position (upper left corner)
           lcd.print("# to Unlock");         // Print some text
           delay(5000);                      //Delay for some time
//           break;                            //End case where any other key is pressed
      }
    break;
    
            // Below is code for running some process after a key is realeased    
 
//    case RELEASED:
//      switch (key){
//        case '*': lcd.clear();
//        break;
//        case'1,2,3,4,5,6,7,8,9,0,#':
//          lcd.setCursor(cole,rowe);
//          cole = cole + 1;
//          if (cole == 16){
//            cole = 1;
//            rowe = rowe + 1;
//          }
//        break;
//      }
//    break;
    

// Depending on what key is pressed we have different courses of action.    
    case HOLD:
      switch (key){
        
        case '*': 
          lcd.clear();
          lcd.home();
          lcd.print("Sleeping now...");
          delay(5000);
          lcd.clear();
          lcd.noDisplay(); 
        break;
        
        case'1,2,3,4,5,6,7,8,9,0,#':
          lcd.clear();
          lcd.home();
          lcd.print("Stop holding key");
          delay(5000);
          lcd.clear();
          lcd.home();
        break;
      }
    break;
  }
}

