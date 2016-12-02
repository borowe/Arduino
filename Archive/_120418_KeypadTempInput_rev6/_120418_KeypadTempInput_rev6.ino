
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

//$$ Setup Program Components - serial port communication, the LCD, the Keypad event listener
void setup(){
  
//  //Debugger
//  Serial.println("Start setup now");
//  Serial.println(t);
//  Serial.println(dt);
//  Serial.println(td);
  
  pinMode(PELTIER,OUTPUT);    //Set pin PELTIER to an output pin
  Serial.begin(9600);        //Start the serial port
  dht.begin();          //Start DHT sensor
  lcd.begin(16,2);      //Start the LCD
  lcd.clear();        //Clear the LCD
  lcd.home();          //Send the LCD to (upper left)
  //keypad.addEventListener(keypadEvent); //add an event listener for the keypad
        
     //      int t = dht.readTemperature()*9/5+32;    //Read the current temp from DHT11 sensor
           
//  //Debugger         
//  Serial.println("End setup now");
//  Serial.println(t);
//  Serial.println(dt);
//  Serial.println(td);
//  delay(10000);
  
}


//$$ Main program loop that is executed and reacts to some keypad event (aka: a key is pressed)
void loop(){
char key = keypad.getKey();
  if (key) {
  Serial.println(key);
  }


// Greeting to Wine-O
     lcd.clear();                      // Clear home
     lcd.home();                       // Return cursor to home position (upper left corner)
     lcd.print("Welcome Traveler");    //Print some text
     delay(1000);                      // Delay for some period
     lcd.setCursor(0,1);               //Set cursor to the second Row first Column
     lcd.print("Let's Drink Wine");       // Print some text
     delay(5000);                      //Delay for some time
     lcd.clear();                      // Clear home
     lcd.home();                       // Return cursor to home position (upper left corner)

     lcd.print("Currently the");       // Print some text
     delay(1000);                      //Delay for some time
     lcd.setCursor(0,1);               //Set cursor to the second Row first Column
     lcd.print("Temperature is:");       // Print some text
     delay(2000);                      //Delay for some time
     lcd.clear();                      // Clear home
     lcd.home();                       // Return cursor to home position (upper left corner)
       Serial.println("Welcome Traveler Finished");


//  Code that runs reading the temperature and humidity w/ error control

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    float t = dht.readTemperature()*9/5+32;
    
    // check if returns are valid, if they are NaN (not a number) then something went wrong!
    if (isnan(t) || isnan(h)) {
      if(isnan(t)){
      lcd.println("Failed to read");
      } 
    }


//  Code to output temperature and humidity readings to LCD
           
    lcd.clear();
    lcd.home();
    lcd.print("Temperature =");
    lcd.setCursor(0,1);
  //  lcd.print(dht.readTemperature()*9/5+32,2);    //Print temperature 
    lcd.print(t,2);
    lcd.setCursor(5,1);
    lcd.print(" degrees F");
    delay(3000);
    lcd.clear();
    lcd.home();
    lcd.print("Humidity =");
    lcd.setCursor(0,1);
  //  lcd.print(dht.readHumidity(),2);    //Print humidity
    lcd.print(h,2);
    lcd.setCursor(5,1);
    lcd.print("%");
    delay(3000);
    lcd.clear();
    lcd.home();
  Serial.println("temperature output finished");



  // Query Wine-O for a desired temperature.
     lcd.print("Enter Desired");       // Print some text
     delay(1000);                      //Delay for some time
     lcd.setCursor(0,1);               //Set cursor to the second Row first Column
     lcd.print("Temperature:");       // Print some text
     lcd.setCursor(12,1);                //Set cursor to the 13th column second row
     lcd.blink();                      //Blink Cursor
       Serial.println("waiting for key input");
     char n1 = keypad.waitForKey();        //capture 10's place digit
     lcd.print(n1);                        //Print 10's digit
     lcd.setCursor(13,1);                //Set cursor to the 14th column second row 
     char n2 = keypad.waitForKey();       //capture 1's place digit
     lcd.print(n2);                        //Print 1's digit
     lcd.noBlink();                  //Turn off blinking display
     delay(1000);                    //Delay for some time

     int in1 = n1 - 48;                  //convert from ASCII #'s to actual decimal math form
     int in2 = n2 - 48;                  //convert from ASCII #'s to actual decimal math form
     int dt = in1 * 10 + in2;          //Create single number from digits input
    

     lcd.clear();                          // Clear LCD
     lcd.home();                            //Send LCD home
     lcd.print("Temp Difference =");        // LCD Print something
     lcd.setCursor(0,1);                    //Set cursor to the first column second row
     int td = dht.readTemperature()*9/5+32-dt;    //Define td as temp difference
     lcd.print(dht.readTemperature()*9/5+32-dt,2);    //Print temperature difference
     lcd.setCursor(6,1);                      // Set LCD cursor to second row column 6
     lcd.print("degrees F");                  // Print something on the LCD
     delay(3000);           //Delay some time
     lcd.clear();
     lcd.home();

//  float t = dht.readTemperature()*9/5+32;           

  Serial.println(t,DEC);
  Serial.println(dt,DEC);
  Serial.println(td,DEC);
  
//  Serial.println("key b4 while");
//  Serial.println(key);
//  delay(1000);
  
  
  
  // Fix this while statement to something meaningful
  while (key != '#'){ 
  
  if (td > 1){
      Serial.println(t,DEC);
      Serial.println(dt,DEC);
      Serial.println(td,DEC);
      delay(1000);
    digitalWrite(PELTIER,HIGH);
    Serial.println("Peltier on");
  } else {
      Serial.println(t,DEC);
      Serial.println(dt,DEC);
      Serial.println(td,DEC);
      delay(1000);
    digitalWrite(PELTIER,LOW);
    Serial.println("Peltier OFF");
  }
  
char key = keypad.getKey();
Serial.println("key value before if key = *");
Serial.print(key);
delay(1000);
  if (key) {
//    lcd.print("Temp =");
//    lcd.setCursor(7,0);
//    lcd.print(t);
//    lcd.setCursor(0,1);
//    lcd.print("Humidity =");
//    lcd.setCursor(11,1);
//    lcd.print(h);
//    delay(3000);
//    lcd.clear();
//    lcd.home();
//  } else {
  Serial.println("new key found in while");
  Serial.println(key);
  delay(1000);
  int test = key - 48;
  Serial.println(test);
  delay(1000);
  
  if(test == 1){
    Serial.println("test equaled 1");
    lcd.print("Temp =");
    lcd.setCursor(7,0);
    lcd.print(t);
    lcd.setCursor(0,1);
    lcd.print("Humidity =");
    lcd.setCursor(11,1);
    lcd.print(h);
    delay(3000);
    lcd.clear();
    lcd.home();
  } else {
  
  break;
  }
  
  //delay(2000);
  }  //End of If (key) loop

}  //End of while loop
}  //End of void loop loop

// When there is a keypad event get the current state: PRESSED, RELEASED OR HOLD, and process code accordingly
void keypadEvent(KeypadEvent key){
//  delay(5000);
  key = keypad.getKey();
//  Serial.println(key);
}





//  switch (keypad.getState()){
//    case PRESSED:{                    // Depending on what key is pressed we have different courses of action.    
//      switch (key){
//        
//// Press # to awaken the wine cooler display.  It then prompts for a desired temperature.
//        case '#':{                     //Start case where # is pressed

//    //Debugger         
//  Serial.println("Start # now");
//  Serial.println(t);
//  Serial.println(dt);
//  Serial.println(td);
//  delay(10000);

           
//                         float t = dht.readTemperature();
//                         Serial.print(t);
           
//           lcd.clear();                      // Clear home
//           lcd.home();                       // Return cursor to home position (upper left corner)
//           lcd.print("Welcome Traveler");    //Print some text
//           delay(1000);                      // Delay for some period
//           lcd.setCursor(0,1);               //Set cursor to the second Row first Column
//           lcd.print("Let's Drink Wine");       // Print some text
//           delay(5000);                      //Delay for some time
//           lcd.clear();                      // Clear home
//           lcd.home();                       // Return cursor to home position (upper left corner)

//           lcd.print("Currently the");       // Print some text
//           delay(1000);                      //Delay for some time
//           lcd.setCursor(0,1);               //Set cursor to the second Row first Column
//           lcd.print("Temperature is:");       // Print some text
//           delay(2000);                      //Delay for some time
//           lcd.clear();                      // Clear home
//           lcd.home();                       // Return cursor to home position (upper left corner)









           
           


  

//           
         
//        break;                               //End case where # is pressed
//        }                  //End of switch case where # is pressed
        
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
    
    
    
    
//      }        //End of switch case for which KEY is pressed
//    }        //End of switch case for keystate PRESSED
    
    
    
    
    
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
//    case HOLD:
//      switch (key){
//        
//        case '*': 
//          lcd.clear();
//          lcd.home();
//          lcd.print("Sleeping now...");
//          delay(5000);
//          lcd.clear();
//          lcd.noDisplay(); 
//        break;
        
//        case'1,2,3,4,5,6,7,8,9,0':
//          lcd.clear();
//          lcd.home();
//          lcd.print("Stop holding key");
//          delay(3000);
//          lcd.clear();
//          lcd.home();
//        break;


//      }              //End of switch case for keystate HOLD

//  }                  // End of switch case for Finding keystate  
  
  
//      //Debugger         
//  Serial.println("End keypad event now");
//  Serial.println(t);
//  Serial.println(dt);
//  Serial.println(td);
//  delay(10000);

//}                    //End of Keypad Event


//
//void enterdesired(){
//
//  
//      //Debugger         
//  Serial.println("Start enterdesired now");
//  Serial.println(t);
//  Serial.println(dt);
//  Serial.println(td);
//  delay(10000);
//  
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
//  
//           int in1 = n1 - 48;                  //convert from ASCII #'s to actual decimal math form
//           int in2 = n2 - 48;                  //convert from ASCII #'s to actual decimal math form
//           int dt = in1 * 10 + in2;          //Create single number from digits input
//          
//
//           lcd.clear();
//           lcd.home();
//           lcd.print("Temp Difference =");
//           lcd.setCursor(0,1);          //Set cursor to the first column second row
//           int td = dht.readTemperature()*9/5+32-dt;    //Print temperature differential
//           lcd.print(dht.readTemperature()*9/5+32-dt,2);    //Print temperature differential
//           lcd.setCursor(6,1);
//           lcd.print("degrees F");
//           delay(3000);
//           
//           int t = dht.readTemperature()*9/5+32;
//           
//           
//                 //Debugger         
//  Serial.println("end enterdesired now");
//  Serial.println(t);
//  Serial.println(dt);
//  Serial.println(td);
//  delay(10000);
//  
//}
