#include <Arduino.h>
#include "ESP8266WiFi.h"
 
 #define ORDER_SIZE 30
const char* ssid = "";
const char* password = "";

char order[ORDER_SIZE] = "";
WiFiServer wifiServer(80);


const int led =  LED_BUILTIN;
// assign the pin A0 to the variable second_pin
const int second_pin = 16;

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
  pinMode(second_pin, OUTPUT);
  //Initialize the serial port
  // put your setup code here, to run once:
}

void loop() {
  //Initialize WifiClient class
  WiFiClient client = wifiServer.available();
  if (!client) {
    return;
  }
  
  while (client.connected())
  {
    while (client.available()) {
      // read each character of the client
      char c = client.read();
      // print the character
      Serial.print(c);
      // if the character is a newline, break out of the loop
      if (c == '\n') break;
    }
  }
}