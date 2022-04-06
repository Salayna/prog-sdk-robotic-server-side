#ifndef CUSTOMCLIENT_H
#define CUSTOMCLIENT_H

#include "ESP8266WiFi.h"
#include <ESP8266WebServer.h>
#include <Arduino.h>

enum class Command {
  AVA,
  REC,
  DRO,
  GAU
};

typedef enum {
  CONNECTED,
  ERR,
  CONNECTING,
} Status;

typedef struct CommandData {
  Command command;
  int value;
} CommandData;


class CustomClient
{
private:
  char* ssid;
  char* password;
  char* server_address;
  int server_port;
  Status status;
  WiFiClient client;
public:
    CustomClient( char* address, int port, char* ssid, char* password);
    ~CustomClient();
    void connect();
    void receiveCommands();
    void disconnect();
    void sendCommand(Command command, int value);  
    Status getStatus();
};
#endif
