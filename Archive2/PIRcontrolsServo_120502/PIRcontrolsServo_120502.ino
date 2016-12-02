
// Servo driven by PIR Sensor
// Whim of ImagineN4tion
// 5.2.2012

#include <Servo.h>
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 

int PIR = 2;      //Define what pin the PIR sensor is on
int PIRval = 0;    //Define variable that will store the analog PIR reading and set to 0
int pos = 0;    //Variable to store the servo position
int servo = 9;    //Define what pin the servo is on


void setup(){
  Serial.begin(9600);  //Start the serial port
  pinMode(PIR, INPUT);
  pinMode(servo, OUTPUT);
    myservo.attach(servo);  // attaches the servo on pin 9 to the servo object 
}


void loop(){
  
  PIRval = digitalRead(PIR);    //Read analog pin A0 and store the value to 'PIR'
  Serial.println("sensor reading =");
  Serial.println(PIRval);    //Print the value stored in PIR to the serial port
  
  if(PIRval == LOW){
    myservo.write(90);
  }
  else{
    myservo.write(180);
  }
  
  
  
//if (PIR > 100){
//  while(pos < 90)  // goes from 0 degrees to 180 degrees 
//  {                                  // in steps of 1 degree 
//    pos += 1;
//    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
//    delay(15);    // waits 15ms for the servo to reach the position 
//    Serial.println("pos = ");
//    Serial.println(pos);
//    PIR = analogRead(0);
//    Serial.println(PIR);
//  } 
//  for(pos > 0; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
//  {                                
//    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
//    delay(15);                       // waits 15ms for the servo to reach the position 
//    Serial.println("pos = ");
//    Serial.println(pos);
//    PIR = analogRead(0);
//    Serial.println(PIR);
//  }
//  pos = 0;
//}

  delay(200);             //Delay 200ms
}


