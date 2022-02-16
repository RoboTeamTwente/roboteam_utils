#pragma once

#include <roboteam_utils/Vector2.h>
#include <roboteam_utils/Angle.h>

#include <vector>

namespace rtt {

enum class KickType {
    NORMAL, // Horizontal kicking
    CHIP    // Diagonally in the air kicking
};

typedef struct RobotCommand {
    unsigned int id = -1;           // [0,15] The id of robot
    
    // Positioning related variables
    Vector2 velocity;               // Target velocity of the robot
    Angle targetAngle;              // (rad) The target angle of the robot
    bool targetAngleIsInVelocity;   // True if target angle should be interpreted as angular velocity
    Angle cameraAngleOfRobot;       // (rad) The current angle of the robot according to the camera
    bool cameraAngleOfRobotSet;     // True if the cameraAngleOfRobot is set
    
    // Action related variables
    bool kickBall;          // Indicates if the robot should kick
    float kickSpeed;        // (m/s) The target speed of the ball
    bool waitForBall;       // Will make the robot wait with kicking untill it has the ball
    KickType kickType;      // Defines the type of kicking, either normal or chipping
    float dribblerSpeed;    // [0, 1] Speed of the dribbler
    
    bool ignorePacket;  // Robot will ignore packet, but robot will reply with feedback
} RobotCommand;

/* This object represents robot commands that are sent from AI to RobotHub */
typedef std::vector<RobotCommand> RobotCommands;

} // namespace rtt