
// PIR Sensor Testing
// Whim of ImagineN4tion
// 5.2.2012

int PIR = 0;    //Set variable that will store the analog read to 0

void setup(){
  Serial.begin(9600);  //Start the serial port
}

void loop(){
  PIR = analogRead(0);    //Read analog pin A0 and store the value to 'PIR'
  Serial.println(PIR);    //Print the value stored in PIR to the serial port
  delay(200);             //Delay 200ms
}


