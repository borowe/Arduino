//  Run a motor's velocity via a pentiometer and output speed to LCD
//  3.16.2012
//  Bob Rowe, Imagine Nation
// "[...] guided by whim, imagination and curiousity."


//LCD Screen setup
#include <LiquidCrystal.h>  //Include the LCD library
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const int motor1 = 6;   // define what pin the motor output (forward) is on
const int motor2 = 5;   // define what pin the second motor output (reverse) is on
int velocity = 0;  //set a variable 'velocity' equal to 0

void setup(){
  Serial.begin(9600);
  pinMode(motor1,OUTPUT);  //Set the pin the motor is on to an output pin
  pinMode(motor2,OUTPUT);  //Set the pin the motor is on to an output pin
  
  lcd.begin(16,2);  //Setup LCD as a 2 line 16 digit LCD
  lcd.blink();  // Set LCD cursor to blink
  lcd.home();  // Send the LCD cursor to the home position - upper left
}

void loop(){
    velocity = analogRead(0);  //read analog value on pin A0
    if (velocity >= 512){
      analogWrite(motor1, (velocity-512)/2);  //write the analog value of A0 (velocity) to the motor output pin
      lcd.print((velocity-512)/2);
    }
    else {
      analogWrite(motor2, velocity/2);
      lcd.print(velocity/2);
    }
      delay(1000);
      lcd.clear();
      lcd.home();  
  Serial.print(velocity);
}


