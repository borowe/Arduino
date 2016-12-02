
// Coffee Stamper Brains
// Whim of ImagineN4tion
// 07.09.2012

#include <Servo.h>  //Include the servo library
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
int servo = 9;    //Define what pin the servo is on

const int R1 = 2;   // define what pin the controls resistor are on
const int R2 = 3;   // define what pin the controls resistor are on
const int R3 = 4;   // define what pin the controls resistor are on
const int R4 = 5;   // define what pin the controls resistor are on

int i = 0;  //set a variable i equal to 0
int d = 2000;  //set a variable for the delay


void setup(){
    pinMode(servo, OUTPUT);
    myservo.attach(servo);  // attaches the servo on pin 9 to the servo object 
    
  pinMode(R1,OUTPUT);  //Set the pin the control resistor is on to an output pin
  pinMode(R2,OUTPUT);  //Set the pin the control resistor is on to an output pin
  pinMode(R3,OUTPUT);  //Set the pin the control resistor is on to an output pin
  pinMode(R4,OUTPUT);  //Set the pin the control resistor is on to an output pin
  Serial.begin(9600);
}


void loop(){

//Stop the servo from rotating
    Serial.println("Stop advancing cups");
    myservo.write(90);   // Write "stop" to the servo
    delay(d/4);          // Delay for 200ms

//Drive stamp forward
    Serial.println("Stamp Forward");
    digitalWrite(R1, HIGH);  //Switch control resistor    
    digitalWrite(R2, HIGH);  //Switch control resistor
    digitalWrite(R3, LOW);  //Switch control resistor
    digitalWrite(R4, LOW);  //Switch control resistor  
    delay(d/10);   //delay for 10ms so we can physically see the change

//Drive stamp back
    Serial.println("Stamp Backward");
    digitalWrite(R1, LOW);  //Switch control resistor    
    digitalWrite(R2, LOW);  //Switch control resistor    
    digitalWrite(R3, HIGH);  //Switch control resistor
    digitalWrite(R4, HIGH);  //Switch control resistor    
    delay(d);   //delay for 10ms so we can physically see the change
    
//Advance the servo forward
    Serial.println("Advance cups");
    myservo.write(180);  // Write "forward" to the servo
    delay(d/4);          // Delay for 200ms


}


