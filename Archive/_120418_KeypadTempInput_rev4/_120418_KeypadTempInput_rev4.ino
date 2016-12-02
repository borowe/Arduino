
//  Program to accept temperature inputs from keypad
//  4.16.2012
//  ImagineN4tion
// "[...] guided by Whim, imagination and curiousity."


//$$ Include Libraries
#include <LiquidCrystal.h>  //Include the LCD library
#include <Keypad.h>         //Include the Kepyad library
#include <DHT.h>            //Include the DHT temp and humidity sensor library

//$$ Configure DHT temp and humidity sensor
#define DHTTYPE DHT11   // we are using a DHT11 as opposed to DHT22 or DHT 21
#define DHTPIN A0
DHT dht(DHTPIN, DHTTYPE);

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

const int PELTIER = 6;
int dt = 0;

//$$ Setup Program Components - serial port communication, the LCD, the Keypad event listener
void setup(){
  pinMode(A1,INPUT);
  pinMode(PELTIER,OUTPUT);
  Serial.begin(9600);
  dht.begin();          //Start DHT sensor
  lcd.begin(16,2);
  lcd.clear();
  lcd.home();
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  
           lcd.print("Enter Desired");       // Print some text
           delay(1000);                      //Delay for some time
           lcd.setCursor(0,1);               //Set cursor to the second Row first Column
           lcd.print("Temperature:");       // Print some text
           lcd.setCursor(12,1);                //Set cursor to the 13th column second row
           lcd.blink();                      //Blink Cursor
           char n1 = keypad.waitForKey();        //capture 10's place digit
           lcd.print(n1);
           lcd.setCursor(13,1);                //Set cursor to the 14th column second row 
           char n2 = keypad.waitForKey();       //capture 1's place digit
           lcd.print(n2);
           lcd.noBlink();                  //Turn off blinking display
           delay(1000);
  
           int in1 = n1 - 48;                  //convert from ASCII #'s to actual decimal math form
           int in2 = n2 - 48;                  //convert from ASCII #'s to actual decimal math form
           int dt = in1 * 10 + in2;          //Create single number from digits input
          

           lcd.clear();
           lcd.home();
           lcd.print("Temp Difference =");
           lcd.setCursor(0,1);          //Set cursor to the first column second row
           int td = dht.readTemperature()*9/5+32-dt;    //Print temperature differential
           lcd.print(dht.readTemperature()*9/5+32-dt,2);    //Print temperature differential
           lcd.setCursor(6,1);
           lcd.print("degrees F");
           delay(3000);
           
           int t = dht.readTemperature()*9/5+32;
  
}


//$$ Main program loop that is executed and reacts to some keypad event (aka: a key is pressed)
void loop(){
  
  char key = keypad.getKey();
//  if (key) {
//  Serial.println(key);
//  }


  int t = dht.readTemperature()*9/5+32;           

  Serial.println(t,DEC);
  Serial.println(dt,DEC);
  int td = t-dt;
  Serial.println(td,DEC);
  
  if (td > 2){
    digitalWrite(PELTIER,HIGH);
  } else {
    digitalWrite(PELTIER,LOW);
  }

}


// When there is a keypad event get the current state: PRESSED, RELEASED OR HOLD, and process code accordingly
void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    case PRESSED:{                    // Depending on what key is pressed we have different courses of action.    
      switch (key){
        
// Press # to awaken the wine cooler display.  It then prompts for a desired temperature.
        case '#':{                     //Start case where # is pressed
      run enterdesired
           
//                         float t = dht.readTemperature();
//                         Serial.print(t);
           
           lcd.display();                    // Turn on LCD display
           lcd.clear();                      // Clear home
           lcd.home();                       // Return cursor to home position (upper left corner)
           lcd.print("Welcome Traveler");    //Print some text
           delay(1000);                      // Delay for some period
           lcd.setCursor(0,1);               //Set cursor to the second Row first Column
           lcd.print("Let's Drink Wine");       // Print some text
           delay(5000);                      //Delay for some time
           lcd.clear();                      // Clear home
           lcd.home();                       // Return cursor to home position (upper left corner)

//           lcd.print("Currently the");       // Print some text
//           delay(1000);                      //Delay for some time
//           lcd.setCursor(0,1);               //Set cursor to the second Row first Column
//           lcd.print("Temperature is:");       // Print some text
//           delay(2000);                      //Delay for some time
//           lcd.clear();                      // Clear home
//           lcd.home();                       // Return cursor to home position (upper left corner)

          for(int i = 0; i < 1; i++){
//            void loop() {
              // Reading temperature or humidity takes about 250 milliseconds!
              // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
//              float h = dht.readHumidity();
              float t = dht.readTemperature()*9/5+32;
            
              // check if returns are valid, if they are NaN (not a number) then something went wrong!
//              if (isnan(t) || isnan(h)) {
                if(isnan(t)){
                lcd.println("Failed to read");
              } else {
//                Serial.print("Humidity: "); 
//                Serial.print(h);
//                Serial.print(" %\t");
//                lcd.print("Temperature: ");
                lcd.print(t);
                lcd.setCursor(5,0);
                lcd.print(" degrees F");
//                Serial.println(" *C");
              }
//            }
              delay(3000);
              lcd.clear();                      // Clear home
              lcd.home();                       // Return cursor to home position (upper left corner)
//}
          }

//Entering desired temp

//goto desired;


//           lcd.print("Enter Desired");       // Print some text
//           delay(1000);                      //Delay for some time
//           lcd.setCursor(0,1);               //Set cursor to the second Row first Column
//           lcd.print("Temperature:");       // Print some text
//           lcd.setCursor(12,1);                //Set cursor to the 13th column second row
//           lcd.blink();                      //Blink Cursor
//           char n1 = keypad.waitForKey();        //capture 10's place digit
//           lcd.print(n1);
//           lcd.setCursor(13,1);                //Set cursor to the 14th column second row 
//           char n2 = keypad.waitForKey();       //capture 1's place digit
//           lcd.print(n2);
//           lcd.noBlink();                  //Turn off blinking display
//           delay(1000);
//           int in1 = n1 - 48;                  //convert from ASCII #'s to actual decimal math form
//           int in2 = n2 - 48;                  //convert from ASCII #'s to actual decimal math form
           
//          Serial.println("in1 =");
//          Serial.println(in1, DEC);
//          Serial.println("in2 =");
//          Serial.println(in2, DEC);
//          Serial.println("Desired Temp =");

//          int dt = in1 * 10 + in2;          //Create single number from digits input
          
//          Serial.println(dt, DEC);
           
           
    //Displaying temp difference
//           lcd.clear();
//           lcd.home();
//           lcd.print("Temp Difference =");
//           lcd.setCursor(0,1);          //Set cursor to the first column second row
//           int td = dht.readTemperature()*9/5+32-dt;    //Print temperature differential
//           lcd.print(dht.readTemperature()*9/5+32-dt,2);    //Print temperature differential
//           lcd.setCursor(6,1);
//           lcd.print("degrees F");
//           delay(3000);
           

  
//  Serial.println(analogRead(1)); 
           
  lcd.clear();
  lcd.home();
  lcd.print("Temperature =");
  lcd.setCursor(0,1);
  lcd.print(dht.readTemperature()*9/5+32,2);    //Print temperature 
  lcd.setCursor(5,1);
  lcd.print(" degrees F");
  delay(3000);
  lcd.clear();
  lcd.home();
  lcd.print("Humidity =");
  lcd.setCursor(0,1);
  lcd.print(dht.readHumidity(),2);    //Print humidity
  lcd.setCursor(5,1);
  lcd.print("%");
  delay(3000);
  lcd.clear();
  lcd.home();
           
         
        break;                               //End case where # is pressed
        }                  //End of switch case where # is pressed
        
//        default:  //Start case where any other key is pressed
//                Serial.println("awake = ");
//                Serial.println(awake);
//           if(awake != 1){
//           lcd.display();                    // Turn on LCD display
//           lcd.clear();                      // Clear home
//           lcd.home();                       // Return cursor to home position (upper left corner)
//           lcd.print("# to Unlock");         // Print some text
//           delay(3000);
//           lcd.clear();                      // Clear home
//           lcd.home();                       // Return cursor to home position (upper left corner)
//           }
//    break;                //End case where any other key is pressed
    
    
    
    
      }        //End of switch case for which KEY is pressed
    }        //End of switch case for keystate PRESSED
    
    
    
    
    
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
    



// Depending on what the keystate is we have different courses of action.    
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
        
//        case'1,2,3,4,5,6,7,8,9,0':
//          lcd.clear();
//          lcd.home();
//          lcd.print("Stop holding key");
//          delay(3000);
//          lcd.clear();
//          lcd.home();
//        break;


      }              //End of switch case for keystate HOLD

  }                  // End of switch case for Finding keystate  

}                    //End of Keypad Event



void enterdesired(){

  
           lcd.print("Enter Desired");       // Print some text
           delay(1000);                      //Delay for some time
           lcd.setCursor(0,1);               //Set cursor to the second Row first Column
           lcd.print("Temperature:");       // Print some text
           lcd.setCursor(12,1);                //Set cursor to the 13th column second row
           lcd.blink();                      //Blink Cursor
           char n1 = keypad.waitForKey();        //capture 10's place digit
           lcd.print(n1);
           lcd.setCursor(13,1);                //Set cursor to the 14th column second row 
           char n2 = keypad.waitForKey();       //capture 1's place digit
           lcd.print(n2);
           lcd.noBlink();                  //Turn off blinking display
           delay(1000);
  
           int in1 = n1 - 48;                  //convert from ASCII #'s to actual decimal math form
           int in2 = n2 - 48;                  //convert from ASCII #'s to actual decimal math form
           int dt = in1 * 10 + in2;          //Create single number from digits input
          

           lcd.clear();
           lcd.home();
           lcd.print("Temp Difference =");
           lcd.setCursor(0,1);          //Set cursor to the first column second row
           int td = dht.readTemperature()*9/5+32-dt;    //Print temperature differential
           lcd.print(dht.readTemperature()*9/5+32-dt,2);    //Print temperature differential
           lcd.setCursor(6,1);
           lcd.print("degrees F");
           delay(3000);
           
           int t = dht.readTemperature()*9/5+32;
  
}
