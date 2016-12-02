
void setup() {
  pinMode(0, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(0, HIGH);
  Serial.println("hello fellow");
  delay(500);
  digitalWrite(0, LOW);
  
  delay(500);
}
