#pragma once

#include <Vector2.h>
#include <Angle.h>
#include <Field.hpp>

#include <vector>

namespace rtt {

typedef struct Ball {
    Vector2 position;
    double height;
    Vector2 velocity;
    double heightVelocity;
    bool isVisible;
} Ball;

typedef struct Robot {
    unsigned int id;        // [0, 15] Id of the robot
    
    Vector2 position;       // Position of the robot relative to field, center of field is 0,0
    Angle angle;            // Angle of the robot relative to the field, counter clockwise
    Vector2 velocity;       // (m/s) Velocity of the robot
    double angularVelocity; // (rad/s) Angular velocity, counter clockwise

    bool xSensIsCalibrated;     // Indicates if the xSens is calibrated. Sending commands before this may result in incorrect calibration
    bool hasWorkingBallSensor;  // Indicates if the robot's ballsensor works
    bool hasBall;               // The robot has the ball
    float ballPositionOnSensor; // [-0.5, 0.5] Position of the ball relative to the ballsensor
    bool hasLockedWheel;        // True if the robot has a blocked wheel

    float signalStrength;
    unsigned int batteryLevel; 
} Robot;

typedef struct World {
    std::vector<Robot> blueRobots;
    std::vector<Robot> yellowRobots;
    Ball ball;
    Field field;
    // TODO: SSL Wrapper packet
    // TODO: SSL Referee packet
    
} World;

} // namespace rtt