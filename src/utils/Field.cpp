#include <Field.hpp>

namespace rtt {

// Default A-Division values according to SSL Rules 2022
// All widths and heights relative to field: width in x, height in y, all in meters
constexpr double DEFAULT_FIELD_WIDTH = 12.0;
constexpr double DEFAULT_FIELD_HEIGHT = 9.0;
constexpr double DEFAULT_PENALTY_WIDTH = 1.8;
constexpr double DEFAULT_PENALTY_HEIGHT = 3.6;
constexpr double DEFAULT_GOAL_HEIGHT = 1.8;
constexpr double DEFAULT_GOAL_WIDTH = 0.18;
constexpr double DEFAULT_BOUNDARY_WIDTH = 0.3;

constexpr double DEFAULT_CENTER_CIRCLE_RADIUS = 0.5;
constexpr Vector2 DEFAULT_CENTER_POINT(0.0, 0.0);
constexpr Circle DEFAULT_CENTER_CIRCLE(DEFAULT_CENTER_POINT, DEFAULT_CENTER_CIRCLE_RADIUS);

constexpr double DEFAULT_PENALTY_POINT_DISTANCE = 8.0;
constexpr Vector2 DEFAULT_LEFT_PENALTY_POINT((DEFAULT_FIELD_WIDTH/2) - DEFAULT_PENALTY_POINT_DISTANCE, 0);
constexpr Vector2 DEFAULT_RIGHT_PENALTY_POINT((-DEFAULT_FIELD_WIDTH/2) + DEFAULT_PENALTY_POINT_DISTANCE, 0);

Field Field::createDefaultField() {
    return createField(DEFAULT_FIELD_WIDTH, DEFAULT_FIELD_HEIGHT, DEFAULT_PENALTY_WIDTH, DEFAULT_PENALTY_HEIGHT, DEFAULT_GOAL_WIDTH, DEFAULT_GOAL_HEIGHT, DEFAULT_BOUNDARY_WIDTH, DEFAULT_CENTER_CIRCLE, DEFAULT_LEFT_PENALTY_POINT, DEFAULT_RIGHT_PENALTY_POINT);
}

Field Field::createField(double fieldWidth, double fieldHeight, double penaltyWidth, double penaltyHeight, double goalWidth, double goalHeight, double boundaryWidth, Circle centerCircle, Vector2 leftPenaltyPoint, Vector2 rightPenaltyPoint) {
    //     A---------------C----------------
    //     |               |               |
    //     E-----         _|_         G----|
    //   I-|    |        / | \        |    K--
    //   | |    |       |  O  |       |    | |
    //   |-J    |        \_|_/        |    |-L
    //     |----F          |          -----H
    //     |               |               |
    //     ----------------B---------------D

    // First, calculate points to easily convert to rectangles
    Vector2 a(-fieldWidth/2, fieldHeight/2);
    Vector2 d(fieldWidth/2, -fieldHeight/2);
    Vector2 b(0,    d.y);
    Vector2 c(0,    a.y);

    Vector2 e(a.x,  penaltyHeight/2);
    Vector2 f(a.x + penaltyWidth, -penaltyHeight/2);

    Vector2 g(d.x - penaltyWidth, penaltyHeight/2);
    Vector2 h(d.x,  -penaltyHeight/2);

    Vector2 i(a.x - goalWidth, goalHeight/2);
    Vector2 j(a.x,  -goalHeight/2);

    Vector2 k(d.x + goalWidth, goalHeight/2);
    Vector2 l(d.x,  -goalHeight/2);

    Field field;

    // Now set the rectangles from these points
    field.playArea          = FieldRectangle(a, d);
    field.leftPlayArea      = FieldRectangle(a, b);
    field.rightPlayArea     = FieldRectangle(c, d);
    field.leftDefenseArea   = FieldRectangle(e, f);
    field.rightDefenseArea  = FieldRectangle(g, h);
    field.leftGoalArea      = FieldRectangle(i, j);
    field.rightGoalArea     = FieldRectangle(k, l);

    // And set remaining variables
    field.boundaryWidth = boundaryWidth;
    field.centerCircle = centerCircle;
    field.leftPenaltyPoint = leftPenaltyPoint;
    field.rightPenaltyPoint = rightPenaltyPoint;

    return field;
}

} // namespace rtt