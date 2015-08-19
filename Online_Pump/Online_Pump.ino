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

void setup()
{
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
              digitalWrite(pin, val);
            }
          }
          sendHeader(client,"Post example");
          //create HTML button to control pin 9
          client.println("<h2>Hot Tub Boat Rentals</h2>");
          client.print(
          "<form action='/' method='POST'><p><input type='hidden' name='pinD9'");
          client.println(" value='0'><input type='submit' value='Stop Filling Boat'/></form>");
          //create HTML button to turn on pin 9
          client.print(
          "<form action='/' method='POST'><p><input type='hidden' name='pinD9'");
          client.print(" value='1'><input type='submit' value='Start Filling Boat'/></form>");
//          client.println("</body></html>");
          
          client.print(
          "<form action='/' method='POST'><p><input type='hidden' name='pinD6'");
          client.println(" value='0'><input type='submit' value='Turn OFF Pump'/></form>");
          //create HTML button to turn on pin 6
          client.print(
          "<form action='/' method='POST'><p><input type='hidden' name='pinD6'");
          client.print(" value='1'><input type='submit' value='Turn ON Pump'/></form>");
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
