#include <ESP8266WiFi.h>

const char* ssid = "TP-LINK_3EAE"; //wifi ssid / wifi name
const char* password = "49836318"; //wifi password

WiFiServer server(80);

#define LED D1            // Led in NodeMCU at pin GPIO16 (D0).
#define ledPin D1 

void setup() {
Serial.begin(115200);
delay(100);
pinMode(LED, OUTPUT);    // LED pin as output.
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) 
{
  delay(100);
  Serial.print(".");
}

Serial.println("");
Serial.println("Connected to WiFi");
Serial.print("IP: ");  Serial.println(WiFi.localIP());
// begin the server
server.begin();
}

void loop() {
  
//digitalWrite(LED, HIGH);// turn the LED off.(Note that LOW is the voltage level but actually 
//                        //the LED is on; this is because it is acive low on the ESP8266.
//delay(1000);            // wait for 1 second.
//digitalWrite(LED, LOW); // turn the LED on.
//delay(1000); // wait for 1 second.

// code
WiFiClient client = server.available();
if (!client) {
return;
}

while(!client.available()){
}

String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();

int value = LOW;
if (request.indexOf("/LED=ON") != -1) 
{
  digitalWrite(ledPin, HIGH);
  value = HIGH;
} 
if (request.indexOf("/LED=OFF") != -1)
{
  digitalWrite(ledPin, LOW);
  value = LOW;
}

client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); //  do not forget this one

client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.print("LED status: "); 

if(value == HIGH) 
{
  client.print("ON");  
} 
else 
{
  client.print("OFF");
}
client.println("<H1 style='font-size:200%'> LED WiFi Control </H1>");
client.println("<br><br>");
client.println("<a href=\" /LED=ON \"> <button style='font-size:200%;color:green'> Turn ON LED</button> </a><br>");
client.println("<a href=\" /LED=OFF \"> <button style='font-size:200%;color:red'> Turn OFF LED</button> </a><br>");
client.println("</html>");

Serial.println("");

}
