/*
 * Stepper_bipolar sketch
 *
 * stepper is controlled from the serial port.
 * a numeric value followed by '+' or '-' steps the motor
 *
 *
 * http://www.arduino.cc/en/Reference/Stepper
 */

#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 24

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 2, 3, 4, 5);

int steps = 0;


void setup()
{
  // set the speed of the motor to 30 RPMs
  stepper.setSpeed(30);
  Serial.begin(9600);
}

void loop()
{
  if ( Serial.available()) {
    char ch = Serial.read();

    if(isDigit(ch)){             // is ch a number?
      steps = steps * 10 + ch - '0';        // yes, accumulate the value
    }
    else if(ch == '+'){
      stepper.step(steps);
      steps = 0;
    }
    else if(ch == '-'){
      stepper.step(steps * -1);
      steps = 0;
    }
  }
}
      
    
