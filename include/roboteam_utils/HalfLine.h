#ifndef RTT_ROBOTEAM_UTILS_SRC_HALFLINE_H_
#define RTT_ROBOTEAM_UTILS_SRC_HALFLINE_H_

#include "Line.h"
#include "Vector2.h"

namespace rtt {
/**
 * The HalfLine class represents a line that is semi-infinite long, i.e. it has an end point where the line stops and an direction in which it is infinite long.
 *
 * @author Haico Dorenbos
 * @since 2020-04-22
 */
class HalfLine {
    private:
        const Vector2 ending; // The location where the HalfLine ends
        const Vector2 direction; // This vector indicates in which direction the HalfLine is infinite long

    public:
        /**
         * Construct a new HalfLine object
         * @param ending The location where the HalfLine ends
         * @param direction This vector indicates in which direction the HalfLine is infinite long
         */
        constexpr HalfLine(const Vector2 &ending, const Vector2 &direction) noexcept : ending{ending}, direction{direction} {};

        /**
         * Compute the intersection point between this HalfLine and the parameter Line.
         *
         * @param line The other line
         * @return std::nullopt in case of no intersection or in case the Halfline lies into the parameter line. Otherwise return the intersection point.
         */
        std::optional<Vector2> intersect(Line line);
};
}
#endif //RTT_ROBOTEAM_UTILS_SRC_HALFLINE_H_
