//example 06 sort of (pg64): control an LED with an analog input from a potentiameter


const int LED = 6;   // define what pin the LED is on
int val = 0;

void setup(){
  Serial.begin(9600);
  pinMode(LED,OUTPUT);  //Set the pin the LED is on to an output pin
}

void loop(){
    val = analogRead(0);  //read analog signal on pin A0
    digitalWrite(LED, HIGH);  //run pin LED high
    delay(val);   //delay for the time specified by the analog signal read from pin A0
    digitalWrite(LED, LOW);  //run pin LED low
    delay(val);  //delay for the time specified by the analog signal read from pin A0
    Serial.print(val);
  }
