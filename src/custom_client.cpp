#include "custom_client.h"

CustomClient::CustomClient( char* address, int port, char* ssid, char* password)
{
  this->ssid = ssid;
  this->password = password;
  this->server_address = address;
  this->server_port = port;
}

 void CustomClient::connect() {
   Serial.print("Conneting...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    this->status = CONNECTING;
  }
  this->status = CONNECTED;
 }

  void CustomClient::receiveCommands() {

    if (this->status == CONNECTED) {
      if (client.available() > 6) {
        char command_string[7];
        //Receveived Data have the following format:
        //<command> <value>
        //Example:
        //DRO 1
        //DRO 0
        //Values can range from 0 to 9
        //Read the first 6 characters
        for (int i = 0; i < 6; i++) {
          command_string[i] = client.read();
        }
        //Add the null terminator
        command_string[6] = '\0';
        char received_command[3];
        char received_value[1];
        //Read the command
        for (int i = 0; i < 3; i++) {
          received_command[i] = command_string[i];
        }
        //Read the value
        for (int i = 3; i < 6; i++) {
          received_value[i - 3] = command_string[i];
        }
        //Convert the command to an enum
        Command command = Command::DRO;
        if (strcmp(received_command, "AVA") == 0) {
          command = Command::AVA;
        } else if (strcmp(received_command, "REC") == 0) {
          command = Command::REC;
        } else if (strcmp(received_command, "DRO") == 0) {
          command = Command::DRO;
        } else if (strcmp(received_command, "GAU") == 0) {
          command = Command::GAU;
        }
        //Convert the value to an int
        int value = atoi(received_value);
        //Send the command to the robot
        this->sendCommand(command, value);
      }
    }
  }

  void CustomClient::sendCommand(Command command, int value) {
    if (this->status == CONNECTED) {
      switch (command) {
        case Command::AVA:
          Serial.println("AVA");
          break;
        case Command::REC:
          Serial.println("REC");
          break;
        case Command::DRO:
          Serial.println("DRO");
          break;
        case Command::GAU:
          Serial.println("GAU");
          break;
      }
    }
  }

Status CustomClient::getStatus() {
  return this->status;
}

void CustomClient::disconnect() {
  WiFi.disconnect();
}

