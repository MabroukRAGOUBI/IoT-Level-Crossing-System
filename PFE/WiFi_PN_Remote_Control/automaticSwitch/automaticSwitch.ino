#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>  //Include the Servo Library
#include <SoftwareSerial.h>
SoftwareSerial arduino(D5,D6);
#include "automaticSwitchWeb.h"; //--> Include the contents of the User Interface Web page from website, stored in the same folder as the .ino file  
#define ServoPort D4    //--> Defining Servo Port
#define ServoPort1 D3
const char* ssid = "ESPServo";  // your SSID
const char* password = "12345678"; //WIFI Password
Servo myservo;  //--> create servo object to control a servo
Servo myservo1;
ESP8266WebServer server(80);  //--> Server on port 80
String SERstate1 = "OFF";
//This routine is executed when you open NodeMCU ESP8266 IP Address in browser
void handleRoot() {
  String s = web_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}
void controlServo() {
  String t_state = server.arg("SERstate1");
  Serial.println(t_state);
  if (t_state == "3") {
   arduino.write("0");  
  }
  else if (t_state == "4") {
   arduino.write("1");
    }
  else {
    SERstate1 = "OFF";
  }
  server.send(200, "text/plane", SERstate1);
}
void statusSER() {
  server.send(200, "text/plane", SERstate1);
}
void setup() {
  arduino.begin(115200);
  myservo.attach(ServoPort); //--> attaches the servo on D1 to the servo object
  myservo1.attach(ServoPort1);
  //* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  //Initialize Webserver
  server.on("/", handleRoot); //--> Routine to handle at root location. This is to display web page.
  server.on("/setSER1", controlServo);
  server.on("/readSER1", statusSER);
  server.begin();
  Serial.println("HTTP server started");}
void loop() {
server.handleClient();
}
