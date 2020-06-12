#include "../include/roboteam_utils/Line.h"
#include "../include/roboteam_utils/LineSegment.h"

namespace rtt {
Line::Line(const Vector2 &location, const Vector2 &direction) {
    this->location = location;
    this->direction = direction;
    if (location == direction) {
        std::cout << "Warning: you created an undefined line, because location == direction. Note that Lines have an infinite length. If you want to have a Line with finite length"
                     " then use the LineSegment class instead." << std::endl;
    }
}

Line::Line(const LineSegment &other) noexcept {
    location = other.start;
    direction = other.end;
    if (location == direction) {
        std::cout << "Warning: you created an undefined line, because location == direction. Note that Lines have an infinite length. If you want to have a Line with finite length"
                     " then use the LineSegment class instead." << std::endl;
    }
}

double Line::distanceToLine(const Vector2 &point) const {
    return (this->project(point) - point).length();
}

Vector2 Line::project(const Vector2 &point) const {
    Vector2 AB = direction - location;
    Vector2 AP = point - location;
    return location + AB * (AP.dot(AB) / AB.length2());
}

std::optional<Vector2> Line::intersect(const Line &line) const {
    return intersect(location, direction, line.location, line.direction);
}

std::optional<Vector2> Line::intersect(const Vector2 line1Location, const Vector2 line1Direction, const Vector2 line2Location, const Vector2 line2Direction) {
    Vector2 A = line1Location - line1Direction;
    Vector2 B = line2Location - line2Direction;
    double denom = A.cross(B);
    if (denom != 0) {
        Vector2 C = line1Location - line2Location;
        double numer = C.cross(A);
        double u = numer / denom;
        return line2Location - B * u;
    }
    return std::nullopt;
}

float Line::relativePosition(Vector2 line1Location, Vector2 line1Direction, Vector2 pointOnLine) {
    float xDiff = line1Direction.x - line1Location.x;
    if (xDiff == 0) {
        return (pointOnLine.y - line1Location.y) / (line1Direction.y - line1Location.y);
    } else {
        return (pointOnLine.x - line1Location.x) / xDiff;
    }
}

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

/*
std::optional<Vector2> Line::intersects(const LineSegment &line) const {
    auto result = intersect(start, end, line.start, line.end);
    if (result.has_value()) {
        float u = relativePosition(line.start, line.end, result.value());
        if (u >= 0 && u <= 1) return std::optional(result.value());
    }
    return std::nullopt;
}

bool Line::doesIntersect(const LineSegment &line) const {
    return intersects(line).has_value();
}

double Line::intercept() const {
    return start.y - this->slope()*start.x;
}

std::pair<double, double> Line::coefficients() const {
    return {slope(), intercept()};
}

bool Line::isParallel(const Line &line) const {
    // check if line is vertical, otherwise check the slope
    if (this->isVertical() || line.isVertical()) {
        return this->isVertical() && line.isVertical();
    }
    return this->slope() == line.slope();
}
bool Line::isParallel(const LineSegment &line) const {
    // check if line is vertical, otherwise check the slope
    if (this->isVertical() || line.isVertical()) {
        return this->isVertical() && line.isVertical();
    }
    return this->slope() == line.slope();
}

bool Line::isOnLine(const Vector2 &point) const {
    if (isPoint()){
        return (start == point || end == point);
    }
    Vector2 A = end - start;
    Vector2 B = point - start;
    return A.cross(B) == 0;
}

double Line::slope() const {
    return (end.y - start.y) / (end.x - start.x);
}

bool Line::isVertical() const {
    return (end.x == start.x) && (end.y != start.y);
}

bool Line::doesIntersect(const Line &line) const {
    return this->intersects(line).has_value();
}
*/
}
