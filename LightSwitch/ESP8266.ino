#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "*********"
#define DEVICE_ID "*********"
#define DEVICE_CREDENTIAL "*********"

#define SSID "*********"
#define SSID_PASSWORD "*********"


WiFiServer server(80); // Set web server port number to 80
String header;// Variable to store the HTTP request

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

String output4State = "off"; //Variables to store the current output state
const int output4 = 4; //Pin 4 is used for output

void setup() {
  Serial.begin(115200); //Start Serial at baud rate 115200
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(4, OUTPUT); //configure pin
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID, SSID_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin(); // start local server
  
  thing.add_wifi(SSID, SSID_PASSWORD); //add wifi to thinger library to start communication to the cloud
  thing["led"] << digitalPin(4); // digital pin control 
}

void loop() {
  thing.handle(); // keep waiting and sending responses to thinger.io

  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             
    String currentLine = ""; // hold incoming data from the client
    while (client.connected()) { 
      if (client.available()) {         
        char c = client.read(); // if there's bytes to read from the client then read a byte
        Serial.write(c);
        header += c;
        // if the byte is a newline character
        if (c == '\n') { 
          // if the current line is blank, then that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK"); //response code
            client.println("Content-type:text/html"); //content type
            client.println("Connection: close");
            client.println();
            
            // turns pin 4 on and off
            if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            }
            
            // HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS  
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Light Switch Web Server</h1>");            
               
            // Display current state, and ON/OFF buttons for pin 4  
            client.println("<p>Light state: " + output4State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    }    
}
