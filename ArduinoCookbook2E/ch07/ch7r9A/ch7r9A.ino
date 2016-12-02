byte pins[] = {2,3,4};
const int NUMBER_OF_PINS = sizeof(pins)/ sizeof(pins[0]);
const int NUMBER_OF_LEDS = NUMBER_OF_PINS * (NUMBER_OF_PINS-1);

byte pairs[NUMBER_OF_LEDS/2][2] = { {0,1}, {1,2}, {0,2} };

int ledStates = 0; //holds states for up to 15 LEDs
int refreshedLed;  // the LED that gets refreshed

void setup()
{
   // nothing here
}

void loop()
{
const int analogInPin = 0; // Analog input pin connected to the variable resistor

  // here is the code from the bargraph recipe
  int sensorValue = analogRead(analogInPin);          // read the analog in value
  int ledLevel = 
    map(sensorValue, 0, 1023, 0, NUMBER_OF_LEDS);    // map to the number of LEDs
    
  for (int led = 0; led < NUMBER_OF_LEDS; led++)
  {
    if (led < ledLevel ) {
      setState(led, HIGH);     // turn on pins less than the level
    }
    else {
      setState(led, LOW);      // turn off pins higher than the level
    }
  }
  ledRefresh();

}

void setState( int led, boolean state)
{
   bitWrite(ledStates,led, state);
}

void ledRefresh()
{
   // refresh a different LED each time this is called.
   if( refreshedLed++ > NUMBER_OF_LEDS) // increment to the next LED
      refreshedLed = 0; // repeat from the first LED if all have been refreshed

   if( bitRead(ledStates, refreshedLed ) == HIGH)
         lightLed( refreshedLed );
}

// this function is identical to the sketch above
// it lights the given LED, the first LED is 0
void lightLed(int led)
{
  // the following four lines convert LED number to pin numbers
  int indexA = pairs[led/2][0];
  int indexB = pairs[led/2][1];
  int pinA = pins[indexA];
  int pinB = pins[indexB];

  // turn off all pins not connected to the given LED
  for(int i=0; i < NUMBER_OF_PINS; i++)
    if( pins[i] != pinA && pins[i] != pinB)
    {  // if this pin is not one of our pins
        pinMode(pins[i], INPUT);   // set the mode to input
        digitalWrite(pins[i],LOW); // make sure pull-up is off
    }
  // now turn on the pins for the given LED
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  if( led % 2 == 0)
  {
     digitalWrite(pinA,LOW);
     digitalWrite(pinB,HIGH);
  }
  else
  {
     digitalWrite(pinB,LOW);
     digitalWrite(pinA,HIGH);
  }
}
      
    
