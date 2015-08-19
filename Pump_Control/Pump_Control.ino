
//#define fadePin 9
int readpin = A0;
int control = 0;

void setup(){
  Serial.begin(9600);
  pinMode(9, OUTPUT);  
  pinMode(readpin, INPUT);
}

void loop(){
  control = analogRead(readpin);
  Serial.println(control);
  delay(500);
  if (control > 150){
  digitalWrite(9, HIGH);
  } else {
    digitalWrite(9, LOW);
  }
  delay(15);
 }


