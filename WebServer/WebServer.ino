/*
 * WebServerPost sketch
 * Turns pin 9 on and off using HTML form
 */

 //The web form will be located at your public IP address followed by
//the port you are using, eg: "ip address:8081"
 //You can find your IP by
 //googling "what's my ip".

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] =  { 192,168,1,177 };

const int MAX_PAGENAME_LEN = 8; // max characters in page name
char buffer[MAX_PAGENAME_LEN+1]; // additional character for terminating null

EthernetServer server(8081);

// Servo Library and setup
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int servo = 6;    //Define what pin the servo is on


void setup()
{
  Serial.begin(9600); //Start serial port for debugging
  myservo.attach(servo);  // attaches the servo on pin 6 to the servo object
  Ethernet.begin(mac, ip);
  server.begin();
  delay(2000);
}

void loop()
{

  EthernetClient client = server.available();
  if (client) {
    int type = 0;
    while (client.connected()) {
        if (client.available()) {
        // GET, POST, or HEAD
        memset(buffer,0, sizeof(buffer)); // clear the buffer
        if(client.readBytesUntil('/', buffer,sizeof(buffer))){
          if(strcmp(buffer,"POST ") == 0){
            client.find("\n\r"); // skip to the body
            // find string starting with "pin", stop on first blank line
            // the POST parameters expected in the form pinDx=Y
            // where x is the pin number and Y is 0 for LOW and 1 for HIGH
            while(client.findUntil("pinD", "\n\r")){
              int pin = client.parseInt();       // the pin number
              int val = client.parseInt();       // 0 or 1
              pinMode(pin, OUTPUT);
              if(pin == 9){
                digitalWrite(pin, val);
              }
              Serial.println(val);
              if(pin == 6){
                myservo.write(val);
              }
            }

      
          }
          sendHeader(client,"Post example");
          //Control of Light
          //create HTML button to control pin 9
          client.println("<h2><font color=#f6a343>IoT - Servo and LED</h2>");
          client.print(
          "<form action='/' method='POST'><p><input type='hidden' name='pinD9'");
          client.println(" value='0'><input type='submit' value='Light Off'/></form>");
          //create HTML button to turn on pin 9
          client.print(
          "<form action='/' method='POST'><p><input type='hidden' name='pinD9'");
          client.print(" value='1'><input type='submit' value='Light On'/></form>");

          //Control of Servo
          //Turn Right
          client.print(
          "<form action='/' method='POST'><p><input type='hidden' name='pinD6'");
          client.println(" value='0'><input type='submit' value='Servo Right'/></form>");
          //Turn Left
          client.print(
          "<form action='/' method='POST'><p><input type='hidden' name='pinD6'");
          client.print(" value='180'><input type='submit' value='Servo Left'/></form>");
          //Stop
          client.print(
          "<form action='/' method='POST'><p><input type='hidden' name='pinD6'");
          client.print(" value='90'><input type='submit' value='Servo Stop'/></form>");
        
          //Create webcam feed
          //client.print("<img name=""FoscamCamera"" src=""http://67.168.78.50:1026/videostream.cgi?user=peon&pwd=noob"" width=""480"" height=""360"" alt=""Live Feed"" style=""background-color: #009999"" />");
        
        
          client.println("</body></html>");
        

        
          client.stop();
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }
}

void sendHeader(EthernetClient client, char *title)
{
  // send a standard http response header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.print("<html><head><title>");
  client.print(title);
  client.println("</title><body>");
} 

