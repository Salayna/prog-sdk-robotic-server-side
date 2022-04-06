#include <Arduino.h>
#include "ESP8266WiFi.h"
#include <ESP8266WebServer.h>
 
 //declare the functions below
  void moveForward();
  void moveBackward();
  void turnLeft();
  void turnRight();
  void stopAll();

 /**
  * 1 / 9 * value
 */

int LEFT_BACK = 5;
int LEFT_FORW = 13;
// Left Motor
int RIGHT_FORW = 16;
int RIGHT_BACK = 14;
int enb = 12;
char command_string[7];
char* ssid = "ESGI";
char* password = "Reseau-GES";
char* server_address = "";
 int server_port = 80;

int DELAY = 5000;


WiFiServer wifiServer(3000);
// Right Motor


const int built_in_led =  LED_BUILTIN;
const String html = "<a href=\"/move_forward\">Move forward</a><br/><a href=\"/move_backward\">Move backward</a><br/><a href=\"/turn_right\">Turn right</a><br/><a href=\"/turn_left\">Turn left</a>";

//create a function to move forward
void moveForward( int value )
{
    Serial.println("Moving Forward...");
    analogWrite(RIGHT_FORW, 127);
    analogWrite(LEFT_FORW, 127);
    delay((3000/9)*value);
    stopAll();
}

//create a function to move backward
void moveBackward( int value)
{
    Serial.println("Moving Backward...");
    Serial.println(value);
    analogWrite(RIGHT_BACK, 127);
    analogWrite(LEFT_BACK, 127);
    delay((3000/9)*value);
    stopAll();
}

//create a function to turn left
void turnLeft(int value)
{
    Serial.println("Turning Left...");
    analogWrite(RIGHT_FORW, 127);
    analogWrite(LEFT_BACK, 0);
    delay((3000/9)*value);
    stopAll();
}

//create a function to turn right
void turnRight(int value)
{
    Serial.println("Turning Right...");
    analogWrite(RIGHT_BACK, 0);
    analogWrite(LEFT_FORW, 127);
    delay((3000/9)*value);
    stopAll();
}

//create a function to stop all
void stopAll()
{
    Serial.println("Stopping...");
    analogWrite(RIGHT_FORW, 0);
    analogWrite(RIGHT_BACK, 0);
    analogWrite(LEFT_FORW, 0);
    analogWrite(LEFT_BACK, 0);
}

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
      while (client.connected()) {
        if (client.available()) {
        for (int i = 0; i < 6; i++) {
          command_string[i] = client.read();
        }
        if (command_string[0] == 'A') {
          moveForward(command_string[4]-48);
        } else if (command_string[0] == 'R') {
          moveBackward(command_string[4]-48);
        } else if (command_string[0] == 'D') {
          turnLeft(command_string[4]-48);
        } else if (command_string[0] == 'G') {
          turnRight(command_string[4]-48);
        }
            }
          }
        }
        client.stop();
  }
}