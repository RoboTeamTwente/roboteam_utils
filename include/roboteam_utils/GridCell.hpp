#pragma once

#include <vector>
#include "Shape.h"

namespace rtt {
class Vector2;

/*
 * This abstract class can be implemented to ensure the derived class can be put into a grid.
 * The grid requires the function to be implemented, and that the derived class has a valid
 * constructor that takes a rectangle (meant for the boundary of the cell)
 */
class GridCell : public Shape {
public:
    virtual ~GridCell() = default;

    // Adds the points this shape has to the given vector. (Recursively for containers like grids)
    virtual void addPoints(std::vector<Vector2>& points) const = 0;
    std::vector<Vector2> getPoints() const {
        std::vector<Vector2> points;
        this->addPoints(points);
        return points;
    }
};

} // namespace rtt