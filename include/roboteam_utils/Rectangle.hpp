#pragma once

#include "Shape.h"
#include "Vector2.h"
#include "LineSegment.h"
#include "GridCell.hpp"

namespace rtt {

class Rectangle : public GridCell {
public:
    virtual ~Rectangle() = default;

    // Gets the width of the rectangle
    [[nodiscard]] virtual double width() const = 0;
    // Gets the height of the rectangle
    [[nodiscard]] virtual double height() const = 0;

    // Gets the largest y value
    [[nodiscard]] virtual double top() const = 0;
    // Gets the smallest x value
    [[nodiscard]] virtual double left() const = 0;
    // Gets the largest x value
    [[nodiscard]] virtual double right() const = 0;
    // Gets the smallest y value
    [[nodiscard]] virtual double bottom() const = 0;

    // Gets the center of the rectangle
    [[nodiscard]] virtual Vector2 center() const = 0;
    // Gets the top left corner
    [[nodiscard]] virtual Vector2 topLeft() const = 0;
    // Gets the top right corner
    [[nodiscard]] virtual Vector2 topRight() const = 0;
    // Gets the bottom left corner
    [[nodiscard]] virtual Vector2 bottomLeft() const = 0;
    // Gets the bottom right corner
    [[nodiscard]] virtual Vector2 bottomRight() const = 0;
    // Gets the top line segment
    [[nodiscard]] virtual LineSegment topLine() const = 0;
    // Gets the left line segment
    [[nodiscard]] virtual LineSegment leftLine() const = 0;
    // Gets the right line segment
    [[nodiscard]] virtual LineSegment rightLine() const = 0;
    // Gets the bottom line segment
    [[nodiscard]] virtual LineSegment bottomLine() const = 0;

    void addPoints(std::vector<Vector2>& points) const override {
        points.push_back(this->center());
    }
};

} // namespace rtt