//
// Created by jesse on 18-05-20.
//

#include "Grid.h"

namespace rtt {
    Grid::Grid(double offSetX, double offSetY, double regionWidth, double regionHeight, int numStepsX, int numStepsY) {
        double stepSizeX = regionWidth/numStepsX;
        double stepSizeY = regionHeight/numStepsY;

        for (int i = 0; i < numStepsX; i++){
            for (int j = 0; j < numStepsY; j++) {
                points[i][j] = Vector2(offSetX + stepSizeX * i, offSetY + stepSizeY * j);
            }
        }
    }

    const std::vector<std::vector<Vector2>> &Grid::getPoints() const {
        return points;
    }

}
