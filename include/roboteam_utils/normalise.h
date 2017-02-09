#pragma once

#include <roboteam_msgs/World.h>
#include <roboteam_msgs/RobotCommand.h>

namespace rtt {

roboteam_msgs::World normalize_world(roboteam_msgs::World world);

/**
 * "Rotates" the robot command. I.e., if you would rotate the field, and then rotate the robot command,
 * the robot would head in the same direction as it would have if you did not do those two rotations.
 * Effectively it only negates the x_vel and y_vel properties of the message.
 */
roboteam_msgs::RobotCommand rotateRobotCommand(roboteam_msgs::RobotCommand const & command);

} // rtt
