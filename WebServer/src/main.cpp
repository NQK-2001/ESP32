#include <Arduino.h>
#include <WiFi.h>
const int LED1 = 4;
const int LED2 = 27;
unsigned currentTime = millis();
unsigned previousTime = 0;
const char *ssid = "Quoc Kiet";
const char *password = "0984166810@";
WiFiServer server(80);
String header;
String output4State = "off";
String output27State = "off";
const long timeoutTime = 2000;

void setup() 
{
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  Serial.print("Connecting WiFi...");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" ");
  Serial.println("WiFi connected.");
  Serial.println("IP Address: ");
  Serial.print(WiFi.localIP());
  server.begin();
}

void loop() 
{
  WiFiClient client = server.available();
  if(client)
  {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client");
    String currentLine = "";
    while(client.connected() && currentTime - previousTime <= timeoutTime )
    {
      currentTime = millis();
      if(client.available())
      {
        char c = client.read();
        Serial.write(c);
        header += c;
        if(c == '\n')
        {
          if(currentLine.length() == 0)
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type: text/html");
            client.println("Connection: close");
            client.println();

            if(header.indexOf("GET /4/on") >= 0)
            {
              Serial.println("GPIO 4 ON");
              output4State = "ON";
              digitalWrite(LED1, HIGH);
            }
            else if (header.indexOf("GET /4/off") >= 0)
            {
              Serial.println("GPIO 4 OFF");
              output4State = "OFF";
              digitalWrite(LED1, LOW);
            }
            else if (header.indexOf("GET /27/on") >= 0)
            {
              Serial.println("GPIO 27 ON");
              output4State = "ON";
              digitalWrite(LED2, HIGH);
            }
            else if (header.indexOf("GET /27/off") >= 0)
            {
              Serial.println("GPIO 27 OFF");
              output4State = "OFF";
              digitalWrite(LED1, LOW);
          }
          //Display HTTL on web page
          client.println("<!DOCTYPE html><html>");
          client.println("<head><meta name =\"viewport\" content=\"width=devices-width, initial-scale=1\">");
          client.println("<link rel=\"icon\" href=\"data:, \">");
          // CSS to style the on/off buttons
          // Feel free to change the background-color and font-size attributes to fit your preferences 
          client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}"); 
          client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;"); 
          client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
          client.println(".button2 {background-color: #555555;}</style></head>");

          // Web Page Heading 
          client.println("<body> <h1>ESP32 Web Server</h1>");
          // Display current state, and ON/OFF buttons for GPIO 4
          client.println("<p>GPIO 4 - State" + output4State + "</p>");
          // If the output26State is off, it displays the ON button 
          if (output4State == "off")
         {
          client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
         }
         else
         {
         client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
         }
         // Display current state, and ON/OFF buttons for GPIO 27
        client.println("<p>GPIO 27 - State"  + output27State + "</p>");
        // If the output27State is off, it displays the ON button
        if (output27State == "off")
        {
        client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
        }
        else
       {
        client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
       }
        client.println("</body></html>");
        // The HTTP response ends with another blank line 
        client.println();
        // Break out of the while loop break;
      }
       else
      { // if you got a newline, then clear currentLine 
      currentLine = "";
      }
      }
       else if (c != '\r')
      { 
  // if you got anything else but a carriage return character, 
      currentLine += c; // add it to the end of the currentline
      }
    }
  }
       // Clear the header variable
      header ="";
      // Close the connection
      client.stop();
      Serial.println("Client disconnected.");
      Serial.println("");
  }  
}
   
