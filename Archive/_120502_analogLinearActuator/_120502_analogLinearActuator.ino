//example 04 (pg57): blink an led like on a sleeping apple computer

const int Linear = 6;   // define what pin the LED is on
int i = 0;  //set a variable i equal to 0
int d = 5;  //set a variable for the delay

void setup(){
  pinMode(Linear,OUTPUT);  //Set the pin the LED is on to an output pin
  Serial.begin(9600);
}

void loop(){
  for(i=0; i<255; i++){  //ramp up the analog signal to LED so light increases
    analogWrite(Linear, i);  //write the analog value of i to the pin the led is on
    delay(d);   //delay for 10ms so we can physically see the change
    Serial.println(i);
  }
  for(i=255; i>0; i--){  //rampd down the analog signal to led so light decreases
    analogWrite(Linear,i);  //write analog value of i to pin the led is on
    delay(d);  //delay for 10ms so we can see the change
        Serial.println(i);
  }
}

