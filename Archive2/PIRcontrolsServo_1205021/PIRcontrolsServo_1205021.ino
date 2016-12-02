
// Servo driven by PIR Sensor
// Whim of ImagineN4tion
// 5.21.2012

#include <Servo.h>
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 

int PIR = 2;      //Define what pin the PIR sensor is on
int PIRval = 0;    //Define variable that will store the PIR reading, set to 0 for now
int servo = 9;    //Define what pin the servo is on


void setup(){
  //Serial.begin(9600);  //Start the serial port
  pinMode(PIR, INPUT);
  pinMode(servo, OUTPUT);
    myservo.attach(servo);  // attaches the servo on pin 9 to the servo object 
}


void loop(){
  
  PIRval = digitalRead(PIR);    //Read the PIR sensor on pin 2 and store the value to 'PIRval'
  //Serial.println("sensor reading =");
  //Serial.println(PIRval);    //Print the value stored in PIR to the serial port
  
  //Note the servo being used here is a continuous rotation servo calibrated so that
  //the servo is stopped at a write value of 90.  Forward = 180, reverse = 0. 
  
  if(PIRval == LOW){    //If there is no movement do nothing
    myservo.write(90);
  }
  else{                  // Else if there is movement drive servo forward
    myservo.write(180);
  }
  
}


