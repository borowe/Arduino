//  Control the Voltage to a Peltier via a pentiometer
//  and output the level to MOSFET to an LCD
//  4.16.2012
//  Bob Rowe, ImagineN4tion
// "[...] guided by Whim, imagination and curiousity."


//LCD Screen setup
#include <LiquidCrystal.h>  //Include the LCD library
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const int temp = 6;   // define what pin the motor output is on
int desiredtemp = 0;  //set a variable 'velocity' equal to 0

void setup(){
  Serial.begin(9600);
  pinMode(temp,OUTPUT);  //Set the pin the LED is on to an output pin
  
  lcd.begin(16,2);  //Setup LCD as a 2 line 16 digit LCD
  lcd.blink();  // Set LCD cursor to blink
  lcd.home();  // Send the LCD cursor to the home position - upper left
}

void loop(){
    desiredtemp = analogRead(0);  //read analog value on pin A0
    analogWrite(temp, desiredtemp/4);  //write the analog value of A0 (velocity) to the motor output pin
    lcd.print(desiredtemp/4);  
    delay(1000);
    lcd.clear();
    lcd.home();  
  Serial.print(desiredtemp);
}


