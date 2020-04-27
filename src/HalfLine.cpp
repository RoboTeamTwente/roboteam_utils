//
// Created by haico on 22-04-20.
//

#include "HalfLine.h"

namespace rtt {
    std::optional<Vector2> HalfLine::intersect(Line line) {
        auto result = Line::generalIntersect(start, direction, line.start, line.end);
        if (result.has_value()) {
            float t = std::get<1>(result.value());
            if (t >= 0) return std::optional(std::get<0>(result.value()));
        }
        return std::nullopt;
    }
}

