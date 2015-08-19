
// Continuous Servo Control for Coffee Cup Stamper
// Whim of ImagineN4tion
// 7.09.2012

#include <Servo.h>
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 

int servo = 9;    //Define what pin the servo is on


void setup(){
  //Serial.begin(9600);  //Start the serial port
  pinMode(servo, OUTPUT);
    myservo.attach(servo);  // attaches the servo on pin 9 to the servo object 
}


void loop(){
  
  //Note the servo being used here is a continuous rotation servo CALIBRATED so that
  //the servo is stopped at a write value of 90.  Forward = 180, reverse = 0. 
  
    myservo.write(90);   // Write "stop" to the servo
    delay(400);          // Delay for 200ms
    myservo.write(180);  // Write "forward" to the servo
    delay(400);          // Delay for 200ms
}


