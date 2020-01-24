//
// Created by rolf on 25-01-20.
//

#ifndef RTT_TUBE_H
#define RTT_TUBE_H
#include "Vector2.h"
#include "LineSegment.h"
namespace rtt{
class Tube {
    public:
        Tube(const Vector2& start, const Vector2& end, double radius);
        Tube(const LineSegment& line, double radius);
        LineSegment line;
        double radius;
        [[nodiscard]] bool contains(const Vector2& point) const;
        std::vector<Vector2> intersects(const LineSegment& line);
        bool doesIntersect(const LineSegment& line);
};
}

#endif //RTT_TUBE_H
