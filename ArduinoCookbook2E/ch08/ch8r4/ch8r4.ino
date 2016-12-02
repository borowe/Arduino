#include <Servo.h>  // the servo library

#define SERVOS 4 // the number of servos
int servoPins[SERVOS] = {7,8,9,10}; // servos on pins 7 through 10

Servo myservo[SERVOS];

void setup()
{
  Serial.begin(9600);
  for(int i=0; i < SERVOS; i++)
    myservo[i].attach(servoPins[i]);
}

void loop()
{
  serviceSerial();
}

// serviceSerial checks the serial port and updates position with received data
// it expects servo data in the form:
//  "180a" writes 180 to servo a
//  "90b writes 90 to servo b
void serviceSerial()
{
  static int pos = 0;

  if ( Serial.available()) {
    char ch = Serial.read();

    if( isDigit(ch) )              // is ch a number?
      pos = pos * 10 + ch - '0';            // yes, accumulate the value
    else if(ch >= 'a' && ch <= 'a'+ SERVOS) // is ch a letter for our servos?
      myservo[ch - 'a'].write(pos);     // yes, save position in position array
  }
}
      
    
