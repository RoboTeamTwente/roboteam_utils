#include "../include/roboteam_utils/Cone.h"
#include "../include/roboteam_utils/Vector2.h"
#include <cmath>
#include "../include/roboteam_utils/Mathematics.h"

namespace rtt {

    Cone::Cone(Vector2 startPoint, Vector2 centerPoint, double distance) {
        start = startPoint;
        center = centerPoint;
        radius = distance;
        if (radius > 0) {
            angle = 2 * atan((radius) / (center - start).length());
        } else {
            // ROS_WARN("radius for cone invalid!");
        }
        side1 = (center - start).rotate(0.5 * angle);
        side2 = (center - start).rotate(-0.5 * angle);
    }

    Cone::Cone(Vector2 startPoint, Vector2 sideA, Vector2 sideB) {
        start = startPoint;
        if (sideA.length() > sideB.length()) {
            side1 = sideA;
            side2 = sideB.stretchToLength(sideA.length());
        } else {
            side1 = sideA.stretchToLength(sideB.length());
            side2 = sideB;
        }
        angle = cleanAngle(side1.angle() - side2.angle());
        center = side2.rotate(0.5 * angle) + start;
        angle = fabs(angle);
        radius = (start + side1 - center).length();
    }

    bool Cone::contains(Vector2 point) const noexcept {
        return IsWithinCone(point, 0.0);
    }










} // rtt
