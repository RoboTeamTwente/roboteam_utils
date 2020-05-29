#include "HalfLine.h"

namespace rtt {
HalfLine::HalfLine(const Vector2 &start, const Vector2 &direction) {
    this->start = start;
    this->direction = direction;
    if (start == direction) {
        std::cout << "Warning: you created an undefined line, because start == direction. Note that HalfLines have an infinite length. If you want to have a Line with finite "
                     "length then use the LineSegment class instead." << std::endl;
    }
}

std::optional<Vector2> HalfLine::intersect(const Line &line) {
    auto result = line.intersect(Line(start, direction));
    if (result.has_value()) {
        float t = Line::relativePosition(start, direction, result.value());
        if (t >= 0) return std::optional(result.value());
    }
    return std::nullopt;
}
}

