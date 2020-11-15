#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "TP-LINK_3EAE"; //wifi ssid / wifi name
const char* password = "49836318"; //wifi password

ESP8266WebServer server(22); //Server on port 80

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
} 

void setup()
{
  Serial.begin(9600);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  server.on("/", handleRoot);  
  server.begin();
  Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
}



void loop()
{
  server.handleClient(); 
}
