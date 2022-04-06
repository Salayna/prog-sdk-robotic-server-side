#include"movement.h"

MovementHandler::MovementHandler(int RIGHT_BACKWARD, int RIGHT_FORWARD, int LEFT_FORWARD, int LEFT_BACKWARD, int enable)
{
    this->RIGHT_BACKWARD = RIGHT_BACKWARD;
    this->RIGHT_FORWARD = RIGHT_FORWARD;
    this->LEFT_FORWARD = LEFT_FORWARD;
    this->LEFT_BACKWARD = LEFT_BACKWARD;
    this->enable = enable;
}

MovementHandler::~MovementHandler()
{
    
}

//create a function to move forward
void MovementHandler::moveForward()
{
    Serial.println("Moving Forward...");
    analogWrite(RIGHT_FORWARD, 127);
    analogWrite(LEFT_FORWARD, 127);
}

//create a function to move backward
void MovementHandler::moveBackward()
{
    Serial.println("Moving Backward...");
    analogWrite(RIGHT_BACKWARD, 127);
    analogWrite(LEFT_BACKWARD, 127);
}

//create a function to turn left
void MovementHandler::turnLeft()
{
    Serial.println("Turning Left...");
    analogWrite(RIGHT_FORWARD, 127);
    analogWrite(LEFT_BACKWARD, 0);
}

//create a function to turn right
void MovementHandler::turnRight()
{
    Serial.println("Turning Right...");
    analogWrite(RIGHT_BACKWARD, 0);
    analogWrite(LEFT_FORWARD, 127);
}

//create a function to stop all
void MovementHandler::stopAll()
{
    Serial.println("Stopping...");
    analogWrite(RIGHT_FORWARD, 0);
    analogWrite(RIGHT_BACKWARD, 0);
    analogWrite(LEFT_FORWARD, 0);
    analogWrite(LEFT_BACKWARD, 0);
}

