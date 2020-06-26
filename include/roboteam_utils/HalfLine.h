#ifndef RTT_ROBOTEAM_UTILS_SRC_HALFLINE_H_
#define RTT_ROBOTEAM_UTILS_SRC_HALFLINE_H_

#include "Line.h"
#include "Vector2.h"

namespace rtt {
/**
 * The HalfLine class represents a line that is semi-infinite long, i.e. it has a start point where the line starts and a direction in which it is infinite long.
 *
 * @author Haico Dorenbos
 * @since 2020-04-22
 */
class HalfLine {
    private:
        Vector2 start; // The location where the HalfLine starts.
        Vector2 goesThrough; // An arbitrary other vector (different than start) through which the HalfLine goes.

    public:
        /**
         * Construct a new HalfLine object by using 2 different points on that HalfLine. Make sure that the given points are different.
         * @param start The location where the HalfLine starts.
         * @param goesThrough An arbitrary other vector through the HalfLine goes (make sure that it is different than the start point).
         */
        explicit HalfLine(const Vector2 &start, const Vector2 &goesThrough);

        /**
         * Compute the intersection point between this HalfLine and the given Line.
         *
         * @param line The given Line.
         * @return std::nullopt in case of no intersection or in case the HalfLine lies into the parameter line. Otherwise return the unique intersection point.
         */
        std::optional<Vector2> intersect(const Line &line);
};
}
#endif //RTT_ROBOTEAM_UTILS_SRC_HALFLINE_H_
