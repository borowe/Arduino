

//Declare LED to define what pin it is on
//as well as define some variable i for our If() loop
const int LED = 6;
int i = 0;

//Set the LED pin to an output
void setup (){
  pinMode(LED,OUTPUT);
}

//loop while increasing the intensity of the LED
void loop(){
  for(i = 0; i < 255; i++){
   analogWrite(LED,i);
   delay(10);
  } 
  
  //loop while decreasing the intensity of the LED
  for(i = 255; i > 0; i--){
    analogWrite(LED,i);
    delay(10);
  }
}

