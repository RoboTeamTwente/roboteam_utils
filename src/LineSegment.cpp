#include "HalfLine.h"
#include "../include/roboteam_utils/Line.h"
#include "../include/roboteam_utils/LineSegment.h"

namespace rtt {
double LineSegment::length() const {
    return (end - start).length();
}

double LineSegment::length2() const {
    return (end - start).length2();
}

bool LineSegment::isPoint() const {
    return start == end;
}

bool LineSegment::doesIntersect(const LineSegment &line) const {
    return intersects(line).has_value();
}

std::optional<Vector2> LineSegment::intersects(const LineSegment &line) const {
    auto result = Line::intersect(start, end, line.start, line.end);
    if (result.has_value()) {
        float t = Line::relativePosition(start, end, result.value());
        float u = Line::relativePosition(line.start, line.end, result.value());
        if (t >= 0 & t <= 1 && u >= 0 && u <= 1) {
            return result;
        } else {
            return std::nullopt;
        }
    } else {
        /* The only possible cases are that one/both of the LineSegments are actually points, the LineSegments have a shared LineSegment part or the LineSegments are distinct and
         * parallel. */
        if (isPoint()) {
            return line.isOnLine(start) ? std::optional<Vector2>(start) : std::nullopt;
        } else if (line.isPoint()) {
            return isOnLine(line.start) ? std::optional<Vector2>(line.start) : std::nullopt;
        }

        // Check if both LineSegments are on the same infinite line.
        Line checkLine = Line(*this);
        if (!checkLine.isOnLine(line.start)) {
            return std::nullopt;
        }
        if (line.isOnFiniteLine(start)) {
            return start;
        } else if (line.isOnFiniteLine(end)) {
            return end;
        } else if (isOnFiniteLine(line.start)) {
            return line.start;
        } else {
            return std::nullopt;
        }
    }
}

double LineSegment::distanceToLine(const Vector2 &point) const {
    return (project(point) - point).length();
}

Vector2 LineSegment::project(const Vector2 &point) const {
    if (isPoint()) {
        return start;
    }
    Vector2 AB = end - start;
    Vector2 AP = point - start;
    double t = AP.dot(AB) / length2();
    if (t < 0) {
        return start;
    }
    else if (t > 1) {
        return end;
    }
    return start + AB * t;
}

bool LineSegment::isOnLine(const Vector2 &point) const {
    if (isPoint()) {
        return (start == point || end == point);
    }
    Vector2 A = end - start;
    Vector2 B = point - start;
    double cross = A.cross(B);
    if (cross != 0) {
        return false;
    }
    float t = Line::relativePosition(start, end, point);
    return t >= 0 && t <= 1;
}

std::vector<Vector2> LineSegment::multiIntersect(const LineSegment &line) const {
    auto result = Line::intersect(start, end, line.start, line.end);
    if (result.has_value()) {
        float t = Line::relativePosition(start, end, result.value());
        float u = Line::relativePosition(line.start, line.end, result.value());
        if (t >= 0 & t <= 1 && u >= 0 && u <= 1) {
            return {result.value()};
        } else {
            return {};
        }
    } else {
        /* The only possible cases are that one/both of the LineSegments are actually points, the LineSegments have a shared LineSegment part or the LineSegments are distinct and
         * parallel. */
        if (isPoint()) {
            if (line.isOnLine(start)) {
                return {start};
            } else {
                return {};
            }
        } else if (line.isPoint()) {
            if (isOnLine(line.start)) {
                return {line.start};
            } else {
                return {};
            }
        }

        // Check if both LineSegments are on the same infinite line.
        Line checkLine = Line(*this);
        if (!checkLine.isOnLine(line.start)) {
            return {};
        }
        std::vector<Vector2> intersections = {};
        if (line.isOnFiniteLine(start)) {
            intersections.push_back(start);
        } else if (line.isOnFiniteLine(end)) {
            intersections.push_back(end);
        } else if (isOnFiniteLine(line.start)) {
            intersections.push_back(line.start);
        } else if (isOnFiniteLine(line.end)) {
            intersections.push_back(line.end);
        }
        std::sort(intersections.begin(), intersections.end());
        intersections.erase(std::unique(intersections.begin(), intersections.end()), intersections.end());
        return intersections;
    }
}

bool LineSegment::operator==(const LineSegment &other) const {
    return ((start == other.start && end == other.end) || (start == other.end && end == other.start));
}

bool LineSegment::isOnFiniteLine(const Vector2 &point) const {
    float t = Line::relativePosition(start, end, point);
    return t >= 0 && t <= 1;
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
bool LineSegment::nonSimpleDoesIntersect(const LineSegment &line) const {
    Vector2 p = start, q = line.start, r = direction(), s = line.direction();
    double denom = r.cross(s);
    double numer = (q - p).cross(r);
    if (denom != 0) {
        double u = numer/denom;
        if (! (u <= 0 || u >= 1)) {
            double t = (q - p).cross(s)/denom;
            if (! (t <= 0 || t >= 1)) {
                return true;
            }
        }
    }
    return false;
}

double LineSegment::slope() const {
    return (end.y - start.y)/(end.x - start.x);
}

double LineSegment::intercept() const {
    return start.y - this->slope()*start.x;
}

std::optional<Vector2> LineSegment::intersects(const Line &line) const {
    Vector2 A = start - end;
    Vector2 B = line.start - line.end;
    double denom = A.cross(B);
    if (denom != 0) {
        Vector2 C = start - line.start;
        double numer = C.cross(B);
        double t = numer/denom;
        if (! (t < 0 || t > 1)) {
            return start - A*t;
        }
    }
    return std::nullopt;
}

bool LineSegment::doesIntersect(const Line &line) const {
    if (intersects(line)) {
        return true;
    }
    return false;
}

// http://geomalgorithms.com/a07-_distance.html#dist3D_Segment_to_Segment
// for implementation hints. This is complicated unfortunately.
double LineSegment::distanceToLine(const LineSegment &line) const {
    Vector2 u = end - start;
    Vector2 v = line.end - line.start;
    Vector2 w = start - line.start;
    double uu = u.dot(u);
    double uv = u.dot(v);
    double vv = v.dot(v);
    double uw = u.dot(w);
    double vw = v.dot(w);
    double D = uu*vv-uv*uv; // Always >=0 by definition

    double sN, sD = D;       // sc = sN / sD, default sD = D >= 0
    double tN, tD = D;       // tc = tN / tD, default tD = D >= 0

    // compute the line parameters of the two closest points
    if (D == 0) { // the lines are parallel
        sN = 0.0;         // force using point start on this segment
        sD = 1.0;         // to prevent possible division by 0.0 later
        tN = vw;
        tD = vv;
    }
    else {                 // get the closest points on the infinite lines
        sN = (uv*vw - vv*uw);
        tN = (uu*vw - uv*uw);
        if (sN < 0.0) {        // sc < 0 => the s=0 edge is visible
            sN = 0.0;
            tN = vw;
            tD = vv;
        }
        else if (sN > sD) {  // sc > 1  => the s=1 edge is visible
            sN = sD;
            tN = vw + uv;
            tD = vv;
        }
    }

    if (tN < 0.0) {            // tc < 0 => the t=0 edge is visible
        tN = 0.0;
        // recompute sc for this edge
        if (-uw < 0.0)
            sN = 0.0;
        else if (-uw > uu)
            sN = sD;
        else {
            sN = -uw;
            sD = uu;
        }
    }
    else if (tN > tD) {      // tc > 1  => the t=1 edge is visible
        tN = tD;
        // recompute sc for this edge
        if ((-uw + uv) < 0.0)
            sN = 0;
        else if ((-uw + uv) > uu)
            sN = sD;
        else {
            sN = (-uw +  uv);
            sD = uu;
        }
    }
    double sc = sN == 0.0 ? 0.0 : sN / sD;
    double tc = tN == 0.0 ? 0.0 : tN / tD;
    Vector2 diff = w + (u * sc) - (v * tc);
    return diff.length();
}

bool LineSegment::isParallel(const LineSegment &line) const {
    // check if line is vertical, otherwise check the slope
    if (this->isVertical() || line.isVertical()) {
        return this->isVertical() && line.isVertical();
    }
    return this->slope() == line.slope();
}
bool LineSegment::isParallel(const Line &line) const {
    // check if line is vertical, otherwise check the slope
    if (this->isVertical() || line.isVertical()) {
        return this->isVertical() && line.isVertical();
    }
    return this->slope() == line.slope();
}
bool LineSegment::isVertical() const {
    return (end.x == start.x) && (end.y != start.y);
}

std::pair<double, double> LineSegment::coefficients() const {
    return {slope(), intercept()};
}
*/
}
