//
// Created by thijs on 28-2-19.
//

#ifndef ANGLE_H
#define ANGLE_H

#include "Math.h"

namespace rtt {
class Vector2;

class Angle {
    public:
        constexpr Angle()
                : angle(0.0) { }

        constexpr Angle(double angle);

        constexpr Angle(const Angle &copy)
                : angle(copy.angle) { }

        double getAngle();
        void setAngle(double angle);

        double angleDiff(Angle &other);
        double angleDiff(double &other);
        double shortestAngleDiff(Angle &other);
        double shortestAngleDiff(double &other);

        rtt::Vector2 toVector2(double length = 1.0);
        bool operator==(const Angle &other) const;
        bool operator!=(const Angle &other) const;

        bool operator<(const Angle &other) const;

        Angle operator+(const Angle &other) const;
        Angle operator+(const double &scalar) const;
        Angle operator-(const Angle &other) const;
        Angle operator-(const double &scalar) const;
        Angle operator+=(const Angle &other);
        Angle operator+=(const double &scalar);
        Angle operator-=(const Angle &other);
        Angle operator-=(const double &scalar);

    private:
        double angle;

        Angle constrain();

};

} // rtt

#endif //ANGLE_H
