//
// Created by thijs on 28-2-19.
//

#include "../include/roboteam_utils/Angle.h"
#include "../include/roboteam_utils/Vector2.h"

namespace rtt {

constexpr Angle::Angle(double angle)
        :angle(angle) {
    this->constrain();
}

double Angle::getAngle() {
    return angle;
}

void Angle::setAngle(double angle) {
    *this = Angle(angle);
}

Angle Angle::constrain() {
    while (angle > M_PI) angle -= 2*M_PI;
    while (angle < - M_PI) angle += 2*M_PI;
    return angle;
}

double Angle::angleDiff(Angle &other) {
    return (*this - other).angle;
}

double Angle::angleDiff(double &scalar) {
    Angle other = Angle(scalar);
    return this->angleDiff(other);
}

double Angle::shortestAngleDiff(Angle &other) {
    if (this->angleDiff(other) > other.angleDiff(*this))
        return other.angleDiff(*this);
    else
        return this->angleDiff(other);
}

double Angle::shortestAngleDiff(double &scalar) {
    Angle other = Angle(scalar);
    return this->shortestAngleDiff(other);
}

rtt::Vector2 Angle::toVector2(double length) {
    rtt::Vector2 vec = rtt::Vector2(cos(this->angle), sin(this->angle));
    return vec.stretchToLength(length);
}

bool Angle::operator==(const Angle &other) const {
    return fabs(this->angle - other.angle) < 0.00001;
}

bool Angle::operator!=(const Angle &other) const {
    return ! (*this == other);
}

bool Angle::operator<(const Angle &other) const {
    return abs(this->angle) < abs(other.angle);
}

Angle Angle::operator+(const Angle &other) const {
    return Angle(this->angle + other.angle);
}

Angle Angle::operator+(const double &scalar) const {
    return Angle(this->angle + scalar);
}

Angle Angle::operator-(const Angle &other) const {
    return Angle(this->angle - other.angle);
}

Angle Angle::operator-(const double &scalar) const {
    return Angle(this->angle - scalar);
}

Angle Angle::operator+=(const Angle &other) {
    *this = *this + other;
    return *this;
}

Angle Angle::operator+=(const double &scalar) {
    Angle other = Angle(scalar);
    return *this += other;
}

Angle Angle::operator-=(const Angle &other) {
    *this = *this - other;
    return *this;
}

Angle Angle::operator-=(const double &scalar) {
    Angle other = Angle(scalar);
    return *this -= other;
}
}