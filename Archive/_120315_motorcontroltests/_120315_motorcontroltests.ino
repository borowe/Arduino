//example 04 (pg57): run a motor's velocity via a pentiometer

const int motor = 6;   // define what pin the LED is on
int velocity = 0;  //set a variable i equal to 0

void setup(){
  //Serial.begin(9600);
  pinMode(motor,OUTPUT);  //Set the pin the LED is on to an output pin
}

void loop(){
    velocity = analogRead(0);  //read analog value on pin A0
    analogWrite(motor, velocity/4);  //write the analog value of A0 (velocity) to the motor output pin
  //Serial.print(velocity/4);
}


