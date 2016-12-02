#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

 
 /*
 *  Simple HTTP get webclient test
 *  https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide
 *  
 */

//#include <ESP8266WiFi.h>

// Define pins that the ultrasonic sensor utilizes
#define TRIGGER 12
#define ECHO 13

// Wifi login credentials
const char* ssid     = "Rouse House";
const char* password = "Kalispel7";

// Site to send GET request to (don't use any "http:" or "/"s in the address)
//const char* host = "www.adafruit.com";
const char* host = "52.25.177.115";

void setup() {
  Serial.begin(115200);
  delay(100);
  
  // Set the pin modes for the ultrasonic sensor's trigger and echo pins
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {

  // ultrasonic stuff
  
  long duration, distance;
  int readCount = 0;
  long aveDistance = 0;
  int goodReads = 0;

  while ( readCount < 5 ) {
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;
  
  if (distance < 200) {
    goodReads = goodReads +1;
    aveDistance = aveDistance + distance;
  }
  
  Serial.println("Centimeter: ");
  Serial.print(distance);
  Serial.println("Average Distance: ");
  Serial.print(aveDistance);
  Serial.println("Good Reads: ");
  Serial.print(goodReads);
  delay(1000);

  readCount = readCount + 1;
  }

  // compute average reading
  aveDistance = aveDistance / goodReads;
  
  // wifi stuff
  delay(5000);
  ++value;
  
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 8080;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  //String url = "/update?level=" + aveDistance;
  String url = "/update?level=";
  url += aveDistance;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}


