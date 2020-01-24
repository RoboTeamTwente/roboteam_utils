//
// Created by rolf on 25-01-20.
//

#include "Tube.h"
#include "LineSegment.h"
namespace rtt {
Tube::Tube(const LineSegment &line, double radius)
        :line{line}, radius{radius} {
}
Tube::Tube(const Vector2 &start, const Vector2 &end, double radius)
        :line{LineSegment(start,end)}, radius{radius} { }
bool Tube::contains(const Vector2 &point) const {
    return line.distanceToLine(point)<=radius;
}
}

