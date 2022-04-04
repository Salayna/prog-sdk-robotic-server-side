#include <Arduino.h>
#include "ESP8266WiFi.h"
 
 #define ORDER_SIZE 30
const char* ssid = "ESGI";
const char* password = "Reseau-GES";

char order[ORDER_SIZE] = "";
WiFiServer wifiServer(80);


int LEFT_FORWARD = 13;
int RIGHT_FORWARD = 5;
int RIGHT_BACK = 4;
int LEFT_BACK = 14;
int DELAY = 1000;


const int led =  LED_BUILTIN;
// assign the pin A0 to the variable second_pin
const int second_pin = 16;

void setup() {
//   WiFi.begin(ssid, password);
//  Serial.begin(9600);
//  Serial.print("Connecting");
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.print(". ");
//   }
//   Serial.println("");
//   Serial.print("Connected to WiFi. IP:");
//   Serial.println(WiFi.localIP());
//   wifiServer.begin();
//   Serial.println("Server started");
//   pinMode(second_pin, OUTPUT);

  //Initialize the serial port
  // put your setup code here, to run once:

  pinMode(LEFT_FORWARD, OUTPUT);    
  pinMode(LEFT_BACK, OUTPUT);    

  pinMode(RIGHT_FORWARD, OUTPUT);  
  pinMode(RIGHT_BACK, OUTPUT); 
}

void loop() {
    
  digitalWrite(RIGHT_FORWARD, HIGH); 
  digitalWrite(LEFT_FORWARD, LOW);   
  delay(DELAY); 

  digitalWrite(RIGHT_FORWARD, LOW); 
  digitalWrite(LEFT_FORWARD, HIGH);                       
  delay(DELAY); 
  // digitalWrite(RIGHT_FORWARD, HIGH);
  // digitalWrite(RIGHT_FORWARD, HIGH);  
  // digitalWrite(RIGHT_BACK, LOW);
  // digitalWrite(LEFT_BACK, LOW);   
  // digitalWrite(LEFT_FORWARD, HIGH); 
  // delay(DELAY);
  //Initialize WifiClient class
  // WiFiClient client = wifiServer.available();
  // if (!client) {
  //   return;
  // }
  
  // while (client.connected())
  // {
  //   while (client.available()) {
  //     // read each character of the client
  //     char c = client.read();
  //     // print the character
  //     Serial.print(c);
  //     // if the character is a newline, break out of the loop
  //     if (c == '\n') break;
  //   }
  // }
  
}