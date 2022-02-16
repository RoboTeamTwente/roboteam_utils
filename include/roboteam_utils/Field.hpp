#pragma once

#include <FieldRectangle.hpp>
#include <Vector2.h>
#include <Grid.h>
#include <Circle.h>

#include <vector>

namespace rtt {

typedef struct Field {
    Vector2 leftPenaltyPoint;   // Place of left penalty point
    Vector2 rightPenaltyPoint;  // Place of right penalty point

    Circle centerCircle;        // Contains the center point and describes the circle around it

    double boundaryWidth;           // Width of the area around the play area

    FieldRectangle playArea;        // The whole field in which robots can drive (excluding goal areas)
    FieldRectangle leftPlayArea;    // Left side of the field
    FieldRectangle rightPlayArea;   // Right side of the field
    FieldRectangle leftDefenseArea; // Left defense area inside left play area
    FieldRectangle rightDefenseArea;// Right defense area inside right play area
    FieldRectangle leftGoalArea;    // Left goal area outside of the play area
    FieldRectangle rightGoalArea;   // Right goal area outside of the play area

    static Field createDefaultField();
    static Field createField(double fieldWidth, double fieldHeight, double penaltyWidth, double penaltyHeight, double goalWidth, double goalHeight, double boundaryWidth, Circle centerCircle, Vector2 leftPenaltyPoint, Vector2 rightPenaltyPoint);
} Field;

} // namespace rtt