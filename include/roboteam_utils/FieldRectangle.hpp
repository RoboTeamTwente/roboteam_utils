#pragma once

#include <Vector2.h>

namespace rtt {

/* A more optimized rectangle class that is used for representing a field.
   Optimized because field data is never edited, but often read */
class FieldRectangle {
public:
    FieldRectangle();
    FieldRectangle(double top, double right, double bottom, double left);
    FieldRectangle(const Vector2& pointA, const Vector2& pointB);

    bool operator==(const FieldRectangle& other) const;

    bool contains(const Vector2& point) const;

    double getTop() const;
    double getRight() const;
    double getBottom() const;
    double getLeft() const;
    double getWidth() const;
    double getHeight() const;
    const Vector2 getCenter() const;

private:
    double top;
    double right;
    double bottom;
    double left;
    double width;
    double height;
    Vector2 center;
};

} // namespace rtt