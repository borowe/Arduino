//example 04 (pg57): blink an led like on a sleeping apple computer

const int LED = 6;   // define what pin the LED is on
int i = 0;  //set a variable i equal to 0

void setup(){
  pinMode(LED,OUTPUT);  //Set the pin the LED is on to an output pin
}

void loop(){
  for(i=0; i<255; i++){  //ramp up the analog signal to LED so light increases
    analogWrite(LED, i);  //write the analog value of i to the pin the led is on
    delay(10);   //delay for 10ms so we can physically see the change
  }
  for(i=255; i>0; i--){  //rampd down the analog signal to led so light decreases
    analogWrite(LED,i);  //write analog value of i to pin the led is on
    delay(10);  //delay for 10ms so we can see the change
  }
}

