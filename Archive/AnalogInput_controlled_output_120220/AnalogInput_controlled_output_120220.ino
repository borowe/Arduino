
//Define output pin and analog read val
const int LED = 6;
int val = 0;


//define pins

void setup(){
  pinMode(LED,OUTPUT);  //define pin LED as output
                        //note: all analog pins are automatically
                        //set as inputs
                        
}

void loop(){
  val = analogRead(0);  //read the incoming analog signal on pin 0
  digitalWrite(LED,HIGH); //set LED pin high
  delay(val);              //delay for time specified by analog input, val
  digitalWrite(LED,LOW);  //set LED pin low
  delay(val);              // delay again for val
}


  
  
