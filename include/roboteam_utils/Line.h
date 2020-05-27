//
// Created by rolf on 18-4-19.
//

#ifndef ROBOTEAM_UTILS_LINE_H
#define ROBOTEAM_UTILS_LINE_H

#include "Vector2.h"

namespace rtt {
class LineSegment;
/**
 * @brief Line class, inherits from Base
 *
 */
class Line {
    public:
    /**
     * @brief Start of the line
     *
     */
    Vector2 start;
    /**
     * @brief End of the line
     *
     */
    Vector2 end;
    
    /**
     * @brief Constructs a new Line object
     *
     * @param start Start of the Line
     * @param end End of the Line
     */
    explicit Line(const Vector2 &start, const Vector2 &end);

    /**
     * @brief Constructs a new Line from a LineSegment.
     * @param other LineSegment to use for construction
     */
    explicit Line(const LineSegment &other) noexcept;
    
    /**
     * @brief Gets the direction of the Line
     *
     * @return Vector2 Vector representation of the direction of this vector
     */
    [[nodiscard]] Vector2 direction() const;

    /**
     * @brief Checks whether line is a single point
     *
     * @return true True if start == end
     * @return false False if start != end
     */
    [[nodiscard]] bool isPoint() const;
    /**
     * @brief Gets the distance from \ref point to the line.
     * The theory behind it is explained in: http://www.randygaul.net/2014/07/23/distance-point-to-line-segment/
     *
     * @param point Point to get distance to
     * @return double Distance to line
     */
    [[nodiscard]] double distanceToLine(const Vector2 &point) const;

    /**
     * @brief Projects the point onto the line
     *
     * @param point Point to get the projection to
     * @return Vector2 Vector projection from the line to the point
     */
    [[nodiscard]] Vector2 project(const Vector2 &point) const;

    /**
     * Get the intersection point between two infinite lines. No intersection point is returned in case the lines are equal or parallel.
     *
     * @param line1Start An arbitrary point on the first line.
     * @param line1End An arbitrary other point on the first line (make sure that it is different than line1Start).
     * @param line2Start An arbitrary point on the second line.
     * @param line2End An arbitrary other point on the second line (make sure that it is different than line2Start).
     * @return std::nullopt if the lines do not intersect or are equal. Otherwise return the intersection point.
     */
    static std::optional<Vector2> intersect(const Vector2 line1Start, const Vector2 line1End, const Vector2 line2Start, const Vector2 line2End);

    /**
     * Get the relative position of pointOnLine on the given infinite line, i.e. compute t such that line1Start + (line1End - line1Start) * t = pointOnLine
     *
     * @param line1Start An arbitrary point on the first line.
     * @param line1End An arbitrary other point on the first line (make sure that it is different than line1Start).
     * @param pointOnLine A point that is located on the given line.
     * @return The value t such that line1Start + (line1End - line1Start) * t = pointOnLine
     */
    static float relativePosition(const Vector2 line1Start, const Vector2 line1End, const Vector2 pointOnLine);

    /* 	 ______   _______  _______  ______     _______  _______  ______   _______
     *	(  __  \ (  ____ \(  ___  )(  __  \   (  ____ \(  ___  )(  __  \ (  ____ \
     *	| (  \  )| (    \/| (   ) || (  \  )  | (    \/| (   ) || (  \  )| (    \/
     *	| |   ) || (__    | (___) || |   ) |  | |      | |   | || |   ) || (__
     *	| |   | ||  __)   |  ___  || |   | |  | |      | |   | || |   | ||  __)
     *	| |   ) || (      | (   ) || |   ) |  | |      | |   | || |   ) || (
     *	| (__/  )| (____/\| )   ( || (__/  )  | (____/\| (___) || (__/  )| (____/\
     *	(______/ (_______/|/     \|(______/   (_______/(_______)(______/ (_______/
     *
     * The functions below are dead. Remove this tag if you use any of the functions and make sure to remove this tag at other places as well that will become alive by using any of the
     * function below. Do not read/document/redesign/analyse/test/optimize/etc. any of this code, because it is a waste of your time! This code was not removed or placed at another
     * branch, because other software developers are very attached to this code and are afraid that this code might be used at some day (but I think it won't be used at all and should
     * be removed).
     */

    /**
     * @brief Gets the intersection of the lines
     * See https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection for help
     *
     * @param line LineSegment to get an intersection from
     * @return std::shared_ptr<Vector2> Vector representation of this intersection
     */
    // [[nodiscard]] std::optional<Vector2> intersects(const LineSegment &line) const;

    /**
     * @brief Checks whether \ref line intersects `this`
     *
     * @param line Line to check against
     * @return true True if \ref line intersects `this`
     * @return false False if \ref line does not intersect `this`
     */
    // [[nodiscard]] bool doesIntersect(const LineSegment &line) const;

    /**
     * @brief Checks whether a \ref point is on the line
     *
     * @param point Point to check `this` against
     * @return true If \ref point is on `this`
     * @return false If \ref point is not on `this`
     */
    // [[nodiscard]] bool isOnLine(const Vector2 &point) const;

    /**
     * @brief Checks whether 2 lines are parralel
     *
     * @param line Other line to check against
     * @return true True if this->slope() == line.slope()
     * @return false False if this->slope() != line.slope()
     */
    // [[nodiscard]] bool isParallel(const Line &line) const;

    /**
     * @brief Checks whether 2 lines are parralel
     *
     * @param line Other line to check against
     * @return true True if this->slope() == line.slope()
     * @return false False if this->slope() != line.slope()
     */
    // [[nodiscard]] bool isParallel(const LineSegment &line) const;

    /**
     * @brief Gets the intercept of this line
     * Literally:
     *      start.y - slope() * start.x;
     * @return double Intercept of this line
     */
    // [[nodiscard]] double intercept() const;

    /**
     * @brief Gets a pair of coefficients
     *
     * @return std::pair<double, double> Pair of doubles where .first == slope() and .second == intercept()
     */
    // [[nodiscard]] std::pair<double, double> coefficients() const;

    /**
     * @brief Gets the slope of this line
     *
     * @return double Slope of the line
     */
    // [[nodiscard]] double slope() const;

    /**
     * @brief Checks whether line is vertical
     *
     * @return true True if line is vertical, will be true if isPoint is true
     * @return false False if line is not vertical
     */
    // [[nodiscard]] bool isVertical() const;

    /**
     * @brief Checks whether \ref line intersects `this`
     *
     * @param line Line to check against
     * @return true if \ref line intersects `this`
     * @return false False if \ref line does not intersect `this`
     */
    // [[nodiscard]] bool doesIntersect(const Line &line) const;

    /**
     * @brief Gets the intersection of the lines
     * See https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection for help
     *
     * @param line Line to get an intersection from
     * @return std::shared_ptr<Vector2> Vector representation of this intersection
     */
    // [[nodiscard]] std::optional<Vector2> intersects(const Line &line) const;
};
}  // namespace rtt

#endif  // ROBOTEAM_UTILS_LINE_H
