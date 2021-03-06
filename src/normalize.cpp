#include "normalize.h"

namespace roboteam_utils {

    float mm_to_m(float scalar) {
        return scalar / 1000.f;
    }

// rotate a ball
    void rotate(proto::WorldBall *ball) {
        assert(ball && "Invalid pointer for ball");
        ball->mutable_pos()->set_x(ball->pos().x() * -1);
        ball->mutable_pos()->set_y(ball->pos().y() * -1);
        ball->mutable_vel()->set_x(ball->vel().x() * -1);
        ball->mutable_vel()->set_y(ball->vel().y() * -1);
    }

// rotate a single robot
    void rotate(proto::WorldRobot *robot) {
        assert(robot && "Invalid pointer for robot");
        robot->mutable_pos()->set_x(robot->pos().x() * -1);
        robot->mutable_pos()->set_y(robot->pos().y() * -1);
        robot->mutable_vel()->set_x(robot->vel().x() * -1);
        robot->mutable_vel()->set_y(robot->vel().y() * -1);
        robot->set_w(robot->w() * -1);
        robot->set_angle(static_cast<float>(rtt::cleanAngle(robot->angle() + M_PI)));
    }

// rotate the ball and robots
    void rotate(proto::World *world) {
        rotate(world->mutable_ball());

        // rotate all blue robots
        for (int i = 0; i < world->mutable_blue()->size(); i++) {
            rotate(world->mutable_blue(i));
        }

        // rotate all yellow robots
        for (int i = 0; i < world->mutable_yellow()->size(); i++) {
            rotate(world->mutable_yellow(i));
        }
    }

// rotate the designated position given by the referee
// this position is used for example for ball placement.
    void rotate(proto::SSL_Referee *refereeData) {
        assert(refereeData && "Invalid pointer for referee");
        refereeData->mutable_designated_position()->set_x(refereeData->designated_position().x() * -1);
        refereeData->mutable_designated_position()->set_y(refereeData->designated_position().y() * -1);
    }

// rotate a single field arc
    void rotate(proto::SSL_FieldCircularArc *arc) {
        assert(arc && "Invalid pointer for arc");
        arc->mutable_center()->set_x(arc->center().x() * -1);
        arc->mutable_center()->set_y(arc->center().y() * -1);
        arc->set_a1(arc->a1() * -1);
        arc->set_a2(arc->a2() * -1);
    }

// rotate a single field line
    void rotate(proto::SSL_FieldLineSegment *line) {
        assert(line && "Invalid pointer for line");
        line->mutable_p1()->set_x(line->p1().x() * -1);
        line->mutable_p1()->set_y(line->p1().y() * -1);
        line->mutable_p2()->set_x(line->p2().x() * -1);
        line->mutable_p2()->set_y(line->p2().y() * -1);
    }

// rotate the lines and arcs of a field
    void rotate(proto::SSL_GeometryFieldSize *field) {
        assert(field && "Invalid pointer for field");
        // rotate all field lines
        for (int i = 0; i < field->mutable_field_lines()->size(); i++) {
            rotate(field->mutable_field_lines(i));
        }

        // rotate all field arcs
        for (int i = 0; i < field->mutable_field_arcs()->size(); i++) {
            rotate(field->mutable_field_arcs(i));
        }
    }

// rotate robotcommands
    void rotate(proto::RobotCommand *command) {
        assert(command && "Invalid pointer for command");
        command->mutable_vel()->set_x(-command->vel().x());
        command->mutable_vel()->set_y(-command->vel().y());
        command->set_w(static_cast<float>(rtt::cleanAngle(command->w() + M_PI)));
    }


} // roboteam_utils
