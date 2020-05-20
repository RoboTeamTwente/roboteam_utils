#include "../include/roboteam_utils/Angle.h"
#include "../include/roboteam_utils/Vector2.h"
#include "../include/roboteam_utils/Definitions.h"

namespace rtt {
    Angle::Angle(double angle) : angle(angle) {
        this->normalize();
    }

    Angle::Angle(const rtt::Vector2 &vec) {
        if (vec.length() < VECTOR_PRECISION)
            angle = 0.0;
        else
            angle = vec.toAngle().getAngle();
    }

    double Angle::getAngle() const noexcept {
        return angle;
    }

    Angle Angle::normalize() noexcept {
        this->angle = fmod(angle + M_PI, 2 * M_PI);
        this->angle = (angle < 0) ? angle + M_PI : angle - M_PI;
        return *this;
    }

    bool Angle::rotateDirection(const Angle &other) const noexcept {
        double angleDiff = other.angle - this->angle;
        bool sign = angleDiff >= 0;
        bool large = fabs(angleDiff) >= M_PI;
        return sign ^ large;
    }

    double Angle::shortestAngleDiff(Angle const &other) const noexcept {
        double thisDiff = abs((*this - other).angle);
        double otherDiff = abs((other - *this).angle);
        return std::min(thisDiff, otherDiff);
    }

    rtt::Vector2 Angle::toVector2(double length) const noexcept {
        rtt::Vector2 vec = rtt::Vector2(cos(this->angle), sin(this->angle));
        return vec.stretchToLength(length);
    }

    bool Angle::operator==(const Angle &other) const noexcept {
        return this->shortestAngleDiff(other) < VECTOR_PRECISION;
    }

    bool Angle::operator!=(const Angle &other) const noexcept {
        return !(*this == other);
    }

    Angle Angle::operator+(const Angle &other) const noexcept {
        return Angle(this->angle + other.angle);
    }

    Angle Angle::operator-(const Angle &other) const noexcept {
        return Angle(this->angle - other.angle);
    }

    Angle &Angle::operator+=(const Angle &other) noexcept {
        this->angle += other.angle;
        this->normalize();
        return *this;
    }

    Angle &Angle::operator-=(const Angle &other) noexcept {
        this->angle -= other.angle;
        this->normalize();
        return *this;
    }

    Angle &Angle::operator=(const double &scalar) noexcept {
        this->angle = scalar;
        this->normalize();
        return *this;
    }
}