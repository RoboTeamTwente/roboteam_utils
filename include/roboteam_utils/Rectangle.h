//
// Created by rolf on 22-01-20.
//

#ifndef ROBOTEAM_UTILS_RECTANGLE_H
#define ROBOTEAM_UTILS_RECTANGLE_H
#include <vector>
#include "Vector2.h"
namespace rtt {
class LineSegment;
class Line;
class Polygon;
/**
 * @brief Represents a rectangle (with horizontal and vertical lines) by storing 2 opposite corners
 * @date 22-01-2020
 * @author Rolf van der Hulst
 */
class Rectangle {
    public:
        Rectangle(const Vector2 &corner, const Vector2 &oppositeCorner);
        Rectangle(Vector2 bottomLeft, double x, double y);
        Vector2 corner1;
        Vector2 corner2;;

        [[nodiscard]] double minX() const;
        [[nodiscard]] double maxX() const;
        [[nodiscard]] double minY() const;
        [[nodiscard]] double maxY() const;
        [[nodiscard]] Vector2 center() const;

        [[nodiscard]] std::vector<Vector2> corners() const;
        [[nodiscard]] std::vector<LineSegment> lines() const;
        [[nodiscard]] Polygon asPolygon() const;

        [[nodiscard]] std::vector<Vector2> intersects(const LineSegment &line) const;
        [[nodiscard]] std::vector<Vector2> intersects(const Line &line) const;
        [[nodiscard]] bool doesIntersect(const LineSegment &line) const;
        [[nodiscard]] bool doesIntersect(const Line &line) const;
        [[nodiscard]] bool contains(const Vector2 &point) const;
        [[nodiscard]] int CohenSutherlandCode(const Vector2 &point) const;
        /**
         * \brief Writes a textual representation of this vector to the given output stream.
         */
        std::ostream &write(std::ostream &out) const;

};

std::ostream &operator<<(std::ostream &out, const Rectangle &rect);

}

#endif //ROBOTEAM_UTILS_RECTANGLE_H
