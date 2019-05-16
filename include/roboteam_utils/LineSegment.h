//
// Created by rolf on 15-5-19.
//

#ifndef ROBOTEAM_UTILS_LINESEGMENT_H
#define ROBOTEAM_UTILS_LINESEGMENT_H
#include "LineBase.h"
namespace rtt {
class LineSegment : public LineBase {
    public:
        constexpr LineSegment(const Vector2 &_start, const Vector2 &_end)
                :LineBase(_start, _end) { };
        double distanceToLine(const Vector2 &point) const override;
        bool isOnLine(const Vector2 &point) const override;
        Vector2 project(const Vector2 &point) const override;
        std::shared_ptr<Vector2> intersects(const Line &line) const override;
        std::shared_ptr<Vector2> intersects(const LineSegment &line) const override;
        bool doesIntersect(const Line &line) const override;
        bool doesIntersect(const LineSegment &line) const override;
        bool nonSimpleDoesIntersect(const LineSegment &line) const;
};
}
#endif //ROBOTEAM_UTILS_LINESEGMENT_H