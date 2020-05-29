#ifndef ROBOTEAM_UTILS_LINE_H
#define ROBOTEAM_UTILS_LINE_H

#include "Vector2.h"

namespace rtt {
class LineSegment;

/**
 * The Line class represents an infinite length Line, it is encoded by two different points through which the Line is infinitely extended in both directions. If you want to use
 * a finite length Line instead then use LineSegment instead.
 * @author Created by: Rolf van der Hulst <br>
 *         Documented and refactored by: Haico Dorenbos
 * @since 2019-04-18
 */
class Line {
    public:
        Vector2 location; // One of the points located on the line, which represents the location of the line.
        Vector2 direction; // Another point located on the line, which should be different than the location. It represents the direction of the line.

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
         * Get the intersection point between two infinite lines. No intersection point is returned in case the lines are equal, parallel or if one of the lines is undefined
         * (a line is undefined if the 2 given points are equal).
         *
         * @param line1Location An arbitrary point on the first line.
         * @param line1Direction An arbitrary other point on the first line.
         * @param line2Location An arbitrary point on the second line.
         * @param line2Direction An arbitrary other point on the second line.
         * @return std::nullopt if the lines do not intersect, are equal or if one of the lines is undefined. Otherwise return the intersection point.
         */
        static std::optional<Vector2> intersect(const Vector2 line1Location, const Vector2 line1Direction, const Vector2 line2Location, const Vector2 line2Direction);

        /**
         * Get the relative position of pointOnLine on the given infinite line, i.e. compute t such that line1Location + (line1Direction - line1Location) * t = pointOnLine. Make sure
         * that the given parameters line1Location and line1Direction are different.
         *
         * @param line1Location An arbitrary point on the first line.
         * @param line1Direction An arbitrary other point on the first line (make sure that it is different than line1Location).
         * @param pointOnLine A point that is located on the given line.
         * @return The value t such that line1Location + (line1Direction - line1Location) * t = pointOnLine
         */
        static float relativePosition(const Vector2 line1Location, const Vector2 line1Direction, const Vector2 pointOnLine);

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
