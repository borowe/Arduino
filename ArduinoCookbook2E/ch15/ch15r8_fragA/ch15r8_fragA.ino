/*
 * Web Server MultiPage Update
 * Respond to requests in the URL to view digital and analog output ports
 * http://192.168.1.177/analog/   displays analog pin data
 * http://192.168.1.177/digital/  displays digital pin data
 * http://192.168.1.177/update/   update (write) pins
 */

#include <SPI.h>         
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] =  { 192,168,1,177 };

const int MAX_PAGE_NAME_LEN = 8+1;  // max characters in a page name + terminating null
char buffer[MAX_PAGE_NAME_LEN];  // make buffer big enough to hold requested page names

EthernetServer server(80);

EthernetClient client;

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println("Ready");
}

void loop()
{
  client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        if( client.find("GET ") ) {
          // look for the page name
          memset(buffer,0, sizeof(buffer)); // clear the buffer
          if(client.find( "/"))  
            if(client.readBytesUntil('/', buffer, MAX_PAGE_NAME_LEN ))  
            {
              if(strcmp(buffer, "analog") == 0)
                showAnalog();
              else if(strcmp(buffer, "digital") == 0)
                showDigital();
              // add this code for new page named: update  
              else if(strcmp(buffer, "update") == 0)
                doUpdate();                
              else
                unknownPage(buffer);
            }
        }
        Serial.println();
        break;
      }
    }
    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }
}

void showAnalog()
{
  Serial.println("analog");
  sendHeader();
  client.println("<h1>Analog Pins</h1>");
  // output the value of each analog input pin

    for (int i = 0; i < 6; i++) {
    client.print("analog pin ");
    client.print(i);
    client.print(" = ");
    client.print(analogRead(i));
    client.println("<br />");
  }
}

void showDigital()
{
  Serial.println("digital");
  sendHeader();
  client.println("<h1>Digital Pins</h1>");
  // show the value of digital pins
  for (int i = 2; i < 8; i++) {
    pinMode(i, INPUT);
    client.print("digital pin ");
    client.print(i);
    client.print(" is ");
    if(digitalRead(i) == LOW)
      client.print("LOW");
    else
      client.print("HIGH");
    client.println("<br />");
  }
  client.println("</body></html>");
}

void unknownPage(char *page)
{
  sendHeader();
  client.println("<h1>Unknown Page</h1>");
  client.print(page);
  client.println("<br />");
  client.println("Recognized pages are:<br />");
  client.println("/analog/<br />");
  client.println("/digital/<br />");
  client.println("</body></html>");
}

void sendHeader()
{
  // send a standard http response header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.println("<html><head><title>Web server multi-page Example</title>");
  client.println("<body>");
}   

void doUpdate()
{
  Serial.println("update");
  sendHeader();
  // find tokens starting with "pin" and stop on the first blank line
  while(client.findUntil("pin", "\n\r")){
    char type = client.read(); // D or A
    int pin = client.parseInt();
    int val = client.parseInt();
    if( type == 'D') {
      Serial.print("Digital pin ");
      pinMode(pin, OUTPUT);
      digitalWrite(pin, val);
    }
    else if( type == 'A'){
      Serial.print("Analog pin ");
      analogWrite(pin, val);
    }
    else {
      Serial.print("Unexpected type ");
      Serial.print(type);
    }
    Serial.print(pin);
    Serial.print("=");
    Serial.println(val);
  }
}

