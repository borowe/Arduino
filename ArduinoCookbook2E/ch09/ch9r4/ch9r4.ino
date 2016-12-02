byte speakerPin = 9;
byte ledPin = 10;

void setup()
{
  pinMode(speakerPin, OUTPUT);
}

void playTone(int period, int duration)
{
// period is one cycle of tone
// duration is how long the pulsing should last in milliseconds
  int pulse = period / 2;
  for (long i = 0; i < duration * 1000L; i += period )
  {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(pulse);
  }
}

void fadeLED(){
 for (int brightness = 0; brightness < 255; brightness++)
 {
   analogWrite(ledPin, brightness);
   delay(2);
  }
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness);
    delay(2);
  }



}
void loop()
{
  // a note with period of 15289 is deep C (second lowest C note on piano)
  for(int period=15289; period >= 477;  period=period / 2)  // play 6 octaves
  {
     playTone( period, 200); // play tone for 200 milliseconds
  }
  fadeLED();
}
      
    
