/*
 * WebServerMultiPageHTMLProgmem sketch
 *
 * Respond to requests in the URL to change digital and analog output ports
 * show the number of ports changed and the value of the analog input pins.
 *
 * http://192.168.1.177/analog/   displays analog pin data
 * http://192.168.1.177/digital/  displays digital pin data
 * http://192.168.1.177/change/  allows changing digital pin data
 *
 * this version uses the F() construct
 */
 
/*
  0 .data         00000104  00800100  00003304  00003398  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  1 .text         00003304  00000000  00000000  00000094  2**1
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  2 .bss          000000f9  00800204  00800204  0000349c  2**0
 */               


#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <TextFinder.h>

#include <avr/pgmspace.h> // for progmem
#define P(name)   static const prog_uchar name[] PROGMEM  // declare a static string

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] =  { 192,168,1,177 };

char buffer[8]; // make this buffer big enough to hold requested page names

Server server(80);

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  delay(3000);
  Serial.println(F("Ready"));
}

void loop()
{

  Client client = server.available();
  if (client) {
    TextFinder  finder(client );
    int type = 0;
    while (client.connected()) {
      if (client.available()) {
        // GET, POST, or HEAD
        if(finder.getString("","/", buffer,sizeof(buffer))){ 
          if(strcmp(buffer, "GET ") == 0 )
            type = 1;
          else if(strcmp(buffer,"POST ") == 0)
            type = 2;
          Serial.print("Type = ");
          Serial.println(type);
          // look for the page name
          if(finder.getString( "", "/", buffer, sizeof(buffer) )) 
          {
            Serial.print(buffer);
            Serial.print("|");
            if(strcasecmp(buffer, "analog") == 0)
              showAnalog(client);
            else if(strcasecmp(buffer, "digital") == 0)
              showDigital(client);
            else if(strcmp(buffer, "change")== 0)
              showChange(client, finder, type == 2);
            else
              unknownPage(client, buffer);
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

void showAnalog(Client client)
{
  Serial.println(F("analog"));
  sendHeader(client,"Multi-page example-Analog");
  client.println("<h1>Analog Pins</h1>");
  // output the value of each analog input pin

  client.println(F("<table border='1' >"));
  for (int i = 0; i < 6; i++) {
    client.print(F("<tr><td>analog pin "));
    client.print(i);
    client.print(F(" </td><td>"));
    client.print(analogRead(i));
    client.println(F("</td></tr>"));
  }
  client.println(F("</table>"));
  client.println(F("</body></html>"));
}

// mime encoded data for the led on and off images:
// see: http://www.motobit.com/util/base64-decoder-encoder.asp
P(led_on) =  "<img src=\"data:image/jpg;base64,"
"/9j/4AAQSkZJRgABAgAAZABkAAD/7AARRHVja3kAAQAEAAAAHgAA/+4ADkFkb2JlAGTAAAAAAf/b"
"AIQAEAsLCwwLEAwMEBcPDQ8XGxQQEBQbHxcXFxcXHx4XGhoaGhceHiMlJyUjHi8vMzMvL0BAQEBA"
"QEBAQEBAQEBAQAERDw8RExEVEhIVFBEUERQaFBYWFBomGhocGhomMCMeHh4eIzArLicnJy4rNTUw"
"MDU1QEA/QEBAQEBAQEBAQEBA/8AAEQgAGwAZAwEiAAIRAQMRAf/EAIIAAAICAwAAAAAAAAAAAAAA"
"AAUGAAcCAwQBAAMBAAAAAAAAAAAAAAAAAAACBAUQAAECBAQBCgcAAAAAAAAAAAECAwARMRIhQQQF"
"UWFxkaHRMoITUwYiQnKSIxQ1EQAAAwYEBwAAAAAAAAAAAAAAARECEgMTBBQhQWEiMVGBMkJiJP/a"
"AAwDAQACEQMRAD8AcNz3BGibKie0nhC0v3A+teKJt8JmZEdHuZalOitgUoHnEpQEWtSyLqgACWFI"
"nixWiaQhsUFFBiQSbiMvvrmeCBp27eLnG7lFTDxs+Kra8oOyium3ltJUAcDIy4EUMN/7Dnq9cPMO"
"W90E9kxeyF2d3HFOQ175olKudUm7TqlfKqDQEDOFR1sNqtC7k5ERYjndNPFSArtvnI/nV+ed9coI"
"ktd2BgozrSZO3J5jVEXRcwD2bbXNdq0zT+BohTyjgPp5SYdPJZ9NP2jsiIz7vhjLohtjnqJ/ouPK"
"co//2Q=="
"\"/>";

P(led_off) = "<img src=\"data:image/jpg;base64,"
"/9j/4AAQSkZJRgABAgAAZABkAAD/7AARRHVja3kAAQAEAAAAHgAA/+4ADkFkb2JlAGTAAAAAAf/b"
"AIQAEAsLCwwLEAwMEBcPDQ8XGxQQEBQbHxcXFxcXHx4XGhoaGhceHiMlJyUjHi8vMzMvL0BAQEBA"
"QEBAQEBAQEBAQAERDw8RExEVEhIVFBEUERQaFBYWFBomGhocGhomMCMeHh4eIzArLicnJy4rNTUw"
"MDU1QEA/QEBAQEBAQEBAQEBA/8AAEQgAHAAZAwEiAAIRAQMRAf/EAHgAAQEAAwAAAAAAAAAAAAAA"
"AAYFAgQHAQEBAQAAAAAAAAAAAAAAAAACAQQQAAECBQAHBQkAAAAAAAAAAAECAwAREhMEITFhoSIF"
"FUFR0UIGgZHBMlIjM1MWEQABAwQDAQEAAAAAAAAAAAABABECIWESA1ETIyIE/9oADAMBAAIRAxEA"
"PwBvl5SWEkkylpJMGsj1XjXSE1kCQuJ8Iy9W5DoxradFa6VDf8IJZAQ6loNtBooTJaqp3DP5oBlV"
"nWrTpEouQS/Cf4PO0uKbqWHGXTSlztSvuVFiZjmfLH3GUuMkzSoTMu8aiNsXet5/17hFyo6PR64V"
"ZnuqfqDDDySFpNpYH3E6aFjzGBr2DkMuFBSFDsWkilUdLftW13pWpcdWqnbBzI/l6hVXKZlROUSe"
"L1KX5zvAPXESjdHsTFWpxLKOJ54hIA1DZCj+Vx/3r96fCNrkvRaT0+V3zV/llplr9sVeHZui/ONk"
"H3dzt6cL/9k="
"\"/>";
;

void showDigital(Client client)
{
  Serial.println(F("digital"));
  sendHeader(client,"Multi-page example-Digital");
  client.println(F("<h2>Digital Pins</h2>"));
  // show the value of digital pins
  client.println(F("<table border='1'>"));
  for (int i = 2; i < 8; i++) {
    pinMode(i, INPUT);
    digitalWrite(i, HIGH); // turn on pull-ups
    client.print(F("<tr><td>digital pin "));
    client.print(i);
    client.print(F(" </td><td>"));
    if(digitalRead(i) == LOW)
      printP(client, led_off);
    else
      printP(client, led_on);
    client.println(F("</td></tr>"));
  }
  client.println(F("</table>"));

  client.println(F("</body></html>"));
}


void showChange(Client client, TextFinder finder, boolean isPost)
{
  Serial.println(F("change"));
  if(isPost)
  {
    Serial.println("isPost");
    finder.find("\n\r"); // skip to the body
    // find parameters starting with "pin" and stop on the first blank line
    Serial.println(F("searching for parms"));
    while(finder.findUntil("pinD", "\n\r")){
      int pin = finder.getValue();       // the pin number
      int val = finder.getValue();       // 0 or 1
      Serial.print(pin);
      Serial.print("=");
      Serial.println(val);
      pinMode(pin, OUTPUT);
      digitalWrite(pin, val);
    }
  }
  sendHeader(client,"Multi-page example-change");
  // table with buttons from 2 through 9
  // 2 to 5 are inputs, the other buttons are outputs

  client.println(F("<table border='1'>"));

  // show the input pins
  for (int i = 2; i < 6; i++) {  // pins 2-5 are inputs
    pinMode(i, INPUT);
    digitalWrite(i, HIGH); // turn on pull-ups
    client.print(F("<tr><td>digital input "));
    client.print(i);
    client.print(F(" </td><td>"));

    client.print(F("&nbsp </td><td>"));
    client.print(F(" </td><td>"));
    client.print(F("&nbsp </td><td>"));


    if(digitalRead(i) == LOW)
      //client.print("Low");
      printP(client, led_off);
    else
      //client.print("high");
    printP(client, led_on);
    client.println("</td></tr>");
  }

  // show output pins 6-9
  // note pins 10-13 are used by the ethernet shield 
  for (int i = 6; i < 10; i++) {
    client.print(F("<tr><td>digital output "));
    client.print(i);
    client.print(F(" </td><td>"));
    htmlButton(client, "On", "pinD", i, "1");
    client.print(F(" </td><td>"));
    client.print(F(" </td><td>"));
    htmlButton(client, "Off", "pinD", i, "0");
    client.print(F(" </td><td>"));

    if(digitalRead(i) == LOW)
      //client.print("Low");
      printP(client, led_off);
    else
      //client.print("high");
    printP(client, led_on);
    client.println(F("</td></tr>"));
  }
  client.println(F("</table>"));
}

// create an HTML button
void htmlButton( Client client, char * label, char *name, int nameId, char *value)
{
  client.print(F("<form action='/change' method='POST'><p><input type='hidden' name='"));
  client.print(name);
  client.print(nameId);
  client.print(F("' value='"));
  client.print(value);
  client.print(F("'><input type='submit' value='"));
  client.print(label);
  client.print(F("'/></form>"));
}

void unknownPage(Client client, char *page)
{
  Serial.print(F("Unknown : "));
  Serial.println(F("page"));

  sendHeader(client,"Unknown Page");
  client.println(F("<h1>Unknown Page</h1>"));
  client.println(page);
  client.println(F("</body></html>"));
}

void sendHeader(Client client, char *title)
{
  // send a standard http response header
  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: text/html"));
  client.println();
  client.print(F("<html><head><title>"));
  client.println(title);
  client.println(F("</title><body>"));
}

void printP(Client client, const prog_uchar *str)
{
  // copy data out of program memory into local storage, write out in
  // chunks of 32 bytes to avoid extra short TCP/IP packets
  // from webduino library Copyright 2009 Ben Combee, Ran Talbott
  uint8_t buffer[32];
  size_t bufferEnd = 0;

  while (buffer[bufferEnd++] = pgm_read_byte(str++))
  {
    if (bufferEnd == 32)
    {
      client.write(buffer, 32);
      bufferEnd = 0;
    }
  }

  // write out everything left but trailing NUL
  if (bufferEnd > 1)
    client.write(buffer, bufferEnd - 1);
}   
