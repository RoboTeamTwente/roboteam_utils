#include "ros/ros.h"
#include "roboteam_utils/Cone.h"
#include "roboteam_utils/LastWorld.h"
#include "roboteam_utils/Vector2.h"
#include "roboteam_msgs/GeometryFieldSize.h"
#include "roboteam_utils/Math.h"

#include <cmath>

namespace rtt {

Cone::Cone(roboteam_utils::Vector2 startPoint, roboteam_utils::Vector2 centerPoint, double distance) {
	start = startPoint;
	center = centerPoint;
	radius = distance;
	if (radius > 0) {
		angle = 2 * asin((radius) / (center-start).length());
	} else {
		ROS_WARN("radius for cone invalid!");
	}
	side1 = (center-start).rotate(0.5*angle);
	side2 = (center-start).rotate(-0.5*angle);
}

Cone::Cone(roboteam_utils::Vector2 startPoint, roboteam_utils::Vector2 side1, roboteam_utils::Vector2 side2) {
	this->start = startPoint;
	roboteam_utils::Vector2 tempSide1 = side1.scale(2 / side1.length());
	roboteam_utils::Vector2 tempSide2 = side2.scale(2 / side2.length());
	this->angle = cleanAngle(tempSide1.angle() - tempSide2.angle());
	this->center = tempSide2.rotate(0.5*angle) + this->start;
	this->side1 = (center-start).rotate(0.5*angle);
	this->side2 = (center-start).rotate(-0.5*angle);
	this->radius = (start+side1 - center).length();
}

bool Cone::IsWithinCone(roboteam_utils::Vector2 point) {
	// ROS_INFO_STREAM("point: " << point.x << " " << point.y);
	roboteam_utils::Vector2 vectorToPoint = point-start;
	roboteam_utils::Vector2 vectorToCenter = center-start;
	// ROS_INFO_STREAM("vectorToPoint: " << vectorToPoint.x << " " << vectorToPoint.y);
	// ROS_INFO_STREAM("vectorToCenter: " << vectorToCenter.x << " " << vectorToCenter.y);
	// ROS_INFO_STREAM("vectorToPoint angle " << vectorToPoint.angle() << " vectorToCenter angle " << vectorToCenter.angle() << " angle " << angle);
	if (fabs(cleanAngle(vectorToPoint.angle() - vectorToCenter.angle())) <= 0.5*angle) {
		return true;
	} else {
		return false;
	}
}

bool Cone::IsWithinCone(roboteam_utils::Vector2 point, double marginRadius) {
	roboteam_utils::Vector2 vectorToPoint = point-start;
	roboteam_utils::Vector2 vectorToCenter = center-start;
	double extraAngle = atan(marginRadius / vectorToPoint.length());

	if (fabs(cleanAngle(vectorToPoint.angle()-vectorToCenter.angle())) < (0.5*angle + extraAngle)) {
		return true;
	} else {
		return false;
	}
}


bool Cone::IsWithinField(roboteam_utils::Vector2 point) {
 	roboteam_msgs::GeometryFieldSize field = LastWorld::get_field();
 	double fieldLimitX = field.field_length / 2.0;
	double fieldLimitY = field.field_width / 2.0;
	if (point.x > fieldLimitX || point.x < -fieldLimitX || point.y > fieldLimitY || point.y < -fieldLimitY) {
		return false;
	} else {
		return true;
	}
}

roboteam_utils::Vector2 Cone::ClosestPointOnSide(roboteam_utils::Vector2 point, roboteam_utils::Vector2 closeTo) {
	if (!IsWithinCone(point)) {
		ROS_WARN("This point is not inside the cone");
		return point;
	}

	roboteam_utils::Vector2 option1 = side1.scale(10 / side1.length()).closestPointOnVector(start, point);
	roboteam_utils::Vector2 option2 = side2.scale(10 / side2.length()).closestPointOnVector(start, point);

	double option1Dist = (closeTo-option1).length();
	double option2Dist = (closeTo-option2).length();

	if (option1Dist <= option2Dist) {
		if (IsWithinField(option1)) return option1;
		else if (IsWithinField(option2)) return option2;
		else return option1;
	} else {
		if (IsWithinField(option2)) return option2;
		else if (IsWithinField(option1)) return option1;
		else return option2;
	}
}

roboteam_utils::Vector2 Cone::SecondClosestPointOnSide(roboteam_utils::Vector2 point) {
	if (!IsWithinCone(point)) {
		ROS_WARN("This point is not inside the cone");
		return point;
	}
	roboteam_utils::Vector2 vectorToPoint = point-start;
	roboteam_utils::Vector2 vectorToCenter = center-start;
	double pointAngle = cleanAngle(vectorToPoint.angle()-vectorToCenter.angle());
	roboteam_utils::Vector2 option1 = vectorToCenter.rotate(angle).scale(vectorToPoint.length() / vectorToCenter.length()) + start;
	roboteam_utils::Vector2 option2 = vectorToCenter.rotate(-angle).scale(vectorToPoint.length() / vectorToCenter.length()) + start;

	if (pointAngle >= 0) {
		if (IsWithinField(option2)) return option2;
		else if (IsWithinField(option1)) return option1;
	} else {
		if (IsWithinField(option1)) return option1;
		else if (IsWithinField(option2)) return option2;
	}
	return point;
}

roboteam_utils::Vector2 Cone::ClosestPointOnSideTwoCones(Cone otherCone, roboteam_utils::Vector2 point, roboteam_utils::Vector2 closeTo, Draw drawer, std::vector<std::string> names) {
	if (!(this->IsWithinCone(point) && otherCone.IsWithinCone(point))) {
		ROS_WARN("This point is not inside either of the cones");
		return point;
	}

	std::vector<roboteam_utils::Vector2> intersections;
	intersections.push_back(LineIntersection(start, side1, otherCone.start, otherCone.side1));
	intersections.push_back(LineIntersection(start, side1, otherCone.start, otherCone.side2));
	intersections.push_back(LineIntersection(start, side2, otherCone.start, otherCone.side1));
	intersections.push_back(LineIntersection(start, side2, otherCone.start, otherCone.side2));

	std::vector<double> costs;
	for (size_t i = 0; i < intersections.size(); i++) {
		// drawer.DrawPoint(names.at(i), intersections.at(i));
		double cost = (intersections.at(i) - closeTo).length()*1 + (intersections.at(i) - point).length()*2;
		costs.push_back(cost);
	}

	int min_pos = distance(costs.begin(), min_element(costs.begin(),costs.end()));
	return intersections.at(min_pos);
}

roboteam_utils::Vector2 Cone::LineIntersection(roboteam_utils::Vector2 line1Start, roboteam_utils::Vector2 line1Dir, roboteam_utils::Vector2 line2Start, roboteam_utils::Vector2 line2Dir) {
	float slope1 = line1Dir.y / line1Dir.x;
	float slope2 = line2Dir.y / line2Dir.x;
	float intersectX = (slope1*line1Start.x - slope2*line2Start.x - line1Start.y + line2Start.y) / (slope1 - slope2);
	float intersectY = slope1 * (intersectX - line1Start.x) + line1Start.y;
	return roboteam_utils::Vector2(intersectX, intersectY);
}

bool Cone::DoConesOverlap(Cone otherCone) {
	if (this->IsWithinCone(otherCone.side1 + otherCone.start) || this->IsWithinCone(otherCone.side2 + otherCone.start) || otherCone.IsWithinCone(side1 + start) || otherCone.IsWithinCone(side2 + start)) {
		return true;
	} else {
		return false;
	}
}

Cone Cone::MergeCones(Cone otherCone) {
	if (!DoConesOverlap(otherCone)) {
		ROS_WARN("No overlap");
		return *this;
	}

	if (this->IsWithinCone(otherCone.side1 + otherCone.start) && this->IsWithinCone(otherCone.side2 + otherCone.start)) {
		return *this;
	}
	if (otherCone.IsWithinCone(side1 + start) && otherCone.IsWithinCone(side2 + start)) {
		return otherCone;

	}

	double angleDiff1 = fabs(cleanAngle(side1.angle() - otherCone.side2.angle()));
	double angleDiff2 = fabs(cleanAngle(side2.angle() - otherCone.side1.angle()));

	if (angleDiff1 > angleDiff2) {
		return Cone(start, side1, otherCone.side2);
	} else {
		return Cone(start, otherCone.side1, side2);
	}
}

Cone::~Cone(){}

} // rtt
