#include "HalfLine.h"

namespace rtt {
HalfLine::HalfLine(const Vector2 &start, const Vector2 &goesThrough) {
    this->start = start;
    this->goesThrough = goesThrough;
    if (start == goesThrough) {
        std::cout << "Warning: you created an undefined line, because start == goesThrough. Note that HalfLines have an infinite length. If you want to have a Line with finite "
                     "length then use the LineSegment class instead." << std::endl;
    }
}

std::optional<Vector2> HalfLine::intersect(const Line &line) {
    auto result = line.intersect(Line(start, goesThrough));
    if (result.has_value()) {
        float t = Line::relativePosition(start, goesThrough, result.value());
        if (t >= 0) return std::optional(result.value());
    }
    return std::nullopt;
}
}

