#pragma once

#include <roboteam_utils/data_objects/Teams.hpp>
#include <roboteam_utils/Vector2.h>
#include <roboteam_utils/Angle.h>

#include <vector>

namespace rtt {

typedef struct RobotStatus {
    unsigned int id; // [0,15] The id of robot

    Vector2 estimatedVelocity;  // The velocity according to the robot
    Angle estimatedAngle;       // The angle according to the robot

    int batteryLevel;           // Voltage level of the LIPO
    bool xSensIsCalibrated;     // The xSens is calibrated
    bool ballSensorIsWorking;   // The ball sensor is working
    bool hasBall;               // The robot has the ball according to the ball sensor
    bool capacitorIsCharged;    // The capacitor is charged
    float ballPositionOnSensor; // [-0.5, 0.5] The position of the ball relative to the ballsensor

    bool frontRightWheelIsLocked;   // Indicates if the front right wheel is locked
    bool backRightWheelIsLocked;    // Indicates if the back  right wheel is locked
    bool backLeftWheelIsLocked;     // Indicates if the back  left  wheel is locked
    bool frontLeftWheelIsLocked;    // Indicates if the front left  wheel is locked

    bool frontRightWheelIsBraking;  // Indicates if the front right wheel is braking
    bool backRightWheelIsBraking;   // Indicates if the back  right wheel is braking
    bool backLeftWheelIsBraking;    // Indicates if the back  left  wheel is braking
    bool frontLeftWheelIsBraking;   // Inidcates if the front left  wheel is braking

    int signalStrength; // Singal strength of the last packet received by the robot
} RobotCommand;

// Represents the origin of the feedback
enum class FeedbackSource {
    SIMULATOR, BASESTATION
};

/* This object represents robot feedback that is sent from RobotHub to World */
typedef struct RobotFeedback {
    std::vector<RobotStatus> robotCommands;
    TeamAbsolute team;
    FeedbackSource feedbackSource;
} RobotCommands;

} // namespace rtt