

// H Bridge Controller for Linear Actuator on Coffee Cup Stamper
// Whim of ImagineN4tion
// 7.09.2012


const int R1 = 2;   // define what pin the controls resistor are on
const int R2 = 3;   // define what pin the controls resistor are on
const int R3 = 4;   // define what pin the controls resistor are on
const int R4 = 5;   // define what pin the controls resistor are on

int i = 0;  //set a variable i equal to 0
int d = 5000;  //set a variable for the delay

void setup(){
  pinMode(R1,OUTPUT);  //Set the pin the control resistor is on to an output pin
  pinMode(R2,OUTPUT);  //Set the pin the control resistor is on to an output pin
  pinMode(R3,OUTPUT);  //Set the pin the control resistor is on to an output pin
  pinMode(R4,OUTPUT);  //Set the pin the control resistor is on to an output pin
  Serial.begin(9600);
}

void loop(){


    Serial.println("Forward");
    digitalWrite(R1, LOW);  //Switch control resistor    
    digitalWrite(R2, LOW);  //Switch control resistor    
    digitalWrite(R3, HIGH);  //Switch control resistor
    digitalWrite(R4, HIGH);  //Switch control resistor    
    delay(d);   //delay for 10ms so we can physically see the change
    
    
    
    Serial.println("Reverse");
    digitalWrite(R1, HIGH);  //Switch control resistor    
    digitalWrite(R2, HIGH);  //Switch control resistor
    digitalWrite(R3, LOW);  //Switch control resistor
    digitalWrite(R4, LOW);  //Switch control resistor  
    delay(d);   //delay for 10ms so we can physically see the change
    


}

