#include "HalfLine.h"

namespace rtt {
    std::optional<Vector2> HalfLine::intersect(Line line) {
        auto result = line.intersect(Line(start, direction));
        if (result.has_value()) {
            float t = Line::relativePosition(start, direction, result.value());
            if (t >= 0) return std::optional(result.value());
        }
        return std::nullopt;
    }
}

