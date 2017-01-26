#include <ros/ros.h>

#include "roboteam_msgs/World.h"
#include "roboteam_msgs/WorldBall.h"

#include "roboteam_utils/LastWorld.h"

namespace rtt {

using namespace roboteam_utils;

void LastWorld::callback_world_state(const roboteam_msgs::WorldConstPtr& world) {
    LastWorld::set(*world);
    LastWorld::received_first_world = true;
}

void LastWorld::callback_geom_data(const roboteam_msgs::GeometryDataConstPtr& geometry) {
    LastWorld::set_field(geometry->field);
    LastWorld::received_first_geom = true;
}

roboteam_msgs::World LastWorld::get() {
    return LastWorld::lastWorld;
}

void LastWorld::set(roboteam_msgs::World world) {
    LastWorld::lastWorld = world;
}

roboteam_msgs::GeometryFieldSize LastWorld::get_field() {
    return LastWorld::field;
}

void LastWorld::set_field(roboteam_msgs::GeometryFieldSize field) {
    LastWorld::field = field;
}

bool LastWorld::have_received_first_world() {
    return LastWorld::received_first_world;
}

bool LastWorld::have_received_first_geom() {
    return LastWorld::received_first_geom;
}

void LastWorld::wait_for_first_messages() {
    ros::Rate fps60(60);

    while (!(rtt::LastWorld::have_received_first_geom() && rtt::LastWorld::have_received_first_world())) {
        fps60.sleep();
        ros::spinOnce();

        if (!ros::ok()) {
            return;
        }
    }
}

roboteam_msgs::Vector2f LastWorld::PredictBallPos(double t) {
	roboteam_msgs::WorldBall ball = lastWorld.ball;
	roboteam_msgs::Vector2f ballVel = ball.vel;
	roboteam_msgs::Vector2f predictedBallPos;
	predictedBallPos.x = ball.pos.x + ballVel.x * t;
	predictedBallPos.y = ball.pos.y + ballVel.y * t;
	return predictedBallPos;
}

Vector2 LastWorld::get_our_goal_center() {
    std::string our_side;
    get_PARAM_OUR_SIDE(our_side, false);
    if (our_side == "left") {
        return Vector2(field.field_length / -2, 0);
    } else {
        return Vector2(field.field_length / 2, 0);
    }
}

Vector2 LastWorld::get_their_goal_center() {
    return get_our_goal_center() * -1;
}

roboteam_msgs::World LastWorld::lastWorld;
roboteam_msgs::GeometryFieldSize LastWorld::field;
bool LastWorld::received_first_geom = false;
bool LastWorld::received_first_world = false;

WorldAndGeomCallbackCreator::WorldAndGeomCallbackCreator()
    : worldSubscriber(n.subscribe<roboteam_msgs::World>(rtt::TOPIC_WORLD_STATE, 1, rtt::LastWorld::callback_world_state))
    , geomSubscriber(n.subscribe<roboteam_msgs::GeometryData>(rtt::TOPIC_GEOMETRY, 1, rtt::LastWorld::callback_geom_data)) {}

}