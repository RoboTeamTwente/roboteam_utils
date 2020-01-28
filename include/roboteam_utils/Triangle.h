//
// Created by rolf on 24-01-20.
//

#ifndef RTT_TRIANGLE_H
#define RTT_TRIANGLE_H
#include "Vector2.h"
namespace rtt {
class LineSegment;
class Line;
class Triangle {
    public:
        Triangle(const Vector2& point1, const Vector2& point2, const Vector2& point3);

        Vector2 corner1;
        Vector2 corner2;
        Vector2 corner3;
        [[nodiscard]] bool contains(const Vector2& point) const;
        [[nodiscard]] double area() const;
        [[nodiscard]] std::vector<LineSegment> lines() const;
        [[nodiscard]] std::vector<Vector2> corners() const;
        [[nodiscard]] std::vector<Vector2> intersects(const LineSegment& line) const;
        [[nodiscard]] std::vector<Vector2> intersects(const Line& line) const;
        [[nodiscard]] bool doesIntersect(const LineSegment& line) const;
        [[nodiscard]] bool doesIntersect(const Line& line) const;
};
}
#endif //RTT_TRIANGLE_H
