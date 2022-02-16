#pragma once

#include <Vector2.h>
#include <Teams.h>

#include <optional>

// Ball location
typedef struct SimulationBallLocation {
    // TODO: Make use of Vector3
    float x; // Center of field is 0.0, from goal to goal in meters
    float y; // Center of field is 0.0, form sideline to sideline in meters
    float z; // Field is at 0.0, from underground to the sky in meters
    float xVelocity; // In meters per second
    float yVelocity; // In meters per second
    float zVelocity; // In meters per second
    bool velocityInRolling = 7; // Will convert the given velocity into rolling speed
    bool teleportSafely = 8;    // Will make sure other robots are moved out of the way, and will not collide with it
    bool byForce = 9;           // Will make sure the ball eventually ends up at the given coordinates by setting a velocity
} SimulationBallLocation;

// Robot location
typedef struct SimulationRobotLocation {
    unsigned int id;
    TeamAbsolute team;      // Either YELLOW or BLUE
    Vector2 position;       // Position on field in meters, center of field is 0,0
    Vector2 velocity;       // (m/s) Velocity of robot relative to field.
    Angle angle;            // Angle of the robot relative to the field
    float angularVelocity;  // (rad/s) Angular velocity of robot, counter clockwise
    bool presentOnField;    // Can make robot disappear
    bool byForce;           // Will make sure the robot eventually ends up at the given coordinates by setting a velocity
} SimulationRobotLocation;

// Robot properties
typedef struct SimulationRobotProperties {
    unsigned int id;
    TeamAbsolute team;      // Either YELLOW or BLUE
    // Units in meters, kilograms, radians, m/s or m/s^2.
    float radius;
    float height;
    float mass;
    float maxKickSpeed;
    float maxChipSpeed;
    float centerToDribblerDistance;
    // Robot limits
    float maxAcceleration;
    float maxAngularAcceleration;
    float maxDeceleration;
    float maxAngularDeceleration;
    float maxVelocity;
    float maxAngularVelocity;
    // Wheel angles. Counter-clockwise starting from dribbler
    float frontRightWheelAngle;
    float backRightWheelAngle;
    float backLeftWheelAngle;
    float frontLeftWheelAngle;
} SimulationRobotProperties;

typedef struct SimulationConfiguration {
    std::optional<SimulationBallLocation> ballLocation;
    std::vector<SimulationRobotLocation> robotLocations;
    std::vector<SimulationRobotProperties> robotProperties;
}

