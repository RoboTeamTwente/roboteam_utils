#ifndef RTT_ROBOTEAM_UTILS_SRC_HALFLINE_H_
#define RTT_ROBOTEAM_UTILS_SRC_HALFLINE_H_

#include "Line.h"
#include "Vector2.h"

namespace rtt {
/**
 * The HalfLine class represents a line that is semi-infinite long, i.e. it has a start point where the line starts and an direction in which it is infinite long.
 *
 * @author Haico Dorenbos
 * @since 2020-04-22
 */
class HalfLine {
    private:
        Vector2 start; // The location where the HalfLine starts
        Vector2 direction; // This vector indicates in which direction the HalfLine is infinite long

    public:
        /**
         * Construct a new HalfLine object by using 2 different points on that Line. Make sure that the given points are different.
         * @param start The location where the HalfLine starts.
         * @param direction This vector indicates in which direction the HalfLine is infinite long (make sure that it is different than the start point).
         */
        explicit HalfLine(const Vector2 &start, const Vector2 &direction);

        /**
         * Compute the intersection point between this HalfLine and the given Line.
         *
         * @param line The given Line
         * @return std::nullopt in case of no intersection or in case the Halfline lies into the parameter line. Otherwise return the unique intersection point.
         */
        std::optional<Vector2> intersect(const Line &line);
};
}
#endif //RTT_ROBOTEAM_UTILS_SRC_HALFLINE_H_
