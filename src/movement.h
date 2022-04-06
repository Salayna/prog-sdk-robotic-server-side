#ifndef MOVEMENTHELPER_H
#define MOVEMENTHELPER_H

#include <Arduino.h>
class MovementHandler
{
private:
    int RIGHT_BACKWARD;
    int RIGHT_FORWARD;
    int LEFT_FORWARD;
    int LEFT_BACKWARD;
    int enable;
public:
    MovementHandler(int RIGHT_BACKWARD, int RIGHT_FORWARD, int LEFT_FORWARD, int LEFT_BACKWARD, int enable);
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();
    void stopAll();
    ~MovementHandler();
};
#endif