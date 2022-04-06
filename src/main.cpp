#include <Arduino.h>
#include "ESP8266WiFi.h"
#include <ESP8266WebServer.h>
#include <custom_client.h>
#include <movement.h>
 
const char* ssid = "ESGI";
const char* password = "Reseau-GES";

WiFiServer wifiServer(3000);
// Right Motor
int RIGHT_BACK = 13;
int RIGHT_FORW = 5;

// Left Motor
int LEFT_FORW = 14;
int LEFT_BACK = 16;
int enb = 12;

int DELAY = 5000;

MovementHandler mov = MovementHandler(RIGHT_BACK, RIGHT_FORW, LEFT_FORW, LEFT_BACK, enb);

const int built_in_led =  LED_BUILTIN;
const String html = "<a href=\"/move_forward\">Move forward</a><br/><a href=\"/move_backward\">Move backward</a><br/><a href=\"/turn_right\">Turn right</a><br/><a href=\"/turn_left\">Turn left</a>";


void setup() {

  WiFi.begin(ssid, password);
 Serial.begin(9600);
 Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(". ");
  }

  Serial.println("");
  Serial.print("Connected to WiFi. IP:");
  Serial.println(WiFi.localIP());
  wifiServer.begin();
  Serial.println("Server started");

  //Initializing pins
  pinMode(built_in_led, OUTPUT);
  pinMode(RIGHT_BACK, OUTPUT);    
  pinMode(LEFT_BACK, OUTPUT);    
  pinMode(RIGHT_FORW, OUTPUT);  
  pinMode(LEFT_FORW, OUTPUT); 
  pinMode(enb, OUTPUT);
  digitalWrite(enb, HIGH);
  //Once Set up is done set the built in led to on
  digitalWrite(built_in_led, HIGH);
}

void loop() {
  if (wifiServer.hasClient()) {
    WiFiClient client = wifiServer.available();
    if (client) {
      String currentLine = "";
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          Serial.write(c);
          if (c == '\n') {
            if (currentLine.length() == 0) {
              client.print("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println("Connection: close");
              client.println();
              client.println(html);
            } else {
              if (currentLine == "move_forward") {
                mov.moveForward();
                client.write("Moving Forward\n");
              } else if (currentLine == "move_backward") {
                mov.moveBackward();
                client.write("Moving Backward\n");
              } else if (currentLine == "turn_right") {
                mov.turnRight();
                client.write("Turning Right\n");
              } else if (currentLine == "turn_left") {
                mov.turnRight();
                client.write("Turning Left\n");
              } else if (currentLine == "stop") {
                mov.stopAll();
                client.write("Stopping\n");
              }
            }
            currentLine = "";
          } else if (c != '\r') {
            currentLine += c;
          }
        }
      }
      client.stop();
    }
  }
}