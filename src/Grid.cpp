//
// Created by jesse on 18-05-20.
//

#include "Grid.h"
namespace rtt {
    Grid::Grid(double offSetX, double offSetY, double regionWidth, double regionHeight, int numStepsX, int numStepsY) :
    offSetX{offSetX},
    offSetY{offSetY},
    regionWidth{regionWidth},
    regionHeight{regionHeight},
    numStepsX{numStepsX},
    numStepsY{numStepsY}
    {
        this->stepSizeX = regionWidth/numStepsX;
        this->stepSizeY = regionHeight/numStepsY;
        for (int i = 0; i < numStepsX; i++) {
            std::vector<Vector2> a;
            points.emplace_back(a);
        }

        for (int i = 0; i < numStepsX; i++) {
            for (int j = 0; j < numStepsY; j++) {
                points[i].emplace_back(Vector2(offSetX + stepSizeX * i, offSetY + stepSizeY * j));
            }
        }
    }

    const std::vector<std::vector<Vector2>> &Grid::getPoints() const {
        return points;
    }

    double Grid::getOffSetX() const {
        return offSetX;
    }

    double Grid::getOffSetY() const {
        return offSetY;
    }

    double Grid::getRegionWidth() const {
        return regionWidth;
    }

    double Grid::getRegionHeight() const {
        return regionHeight;
    }

    int Grid::getNumStepsX() const {
        return numStepsX;
    }

    int Grid::getNumStepsY() const {
        return numStepsY;
    }

    double Grid::getStepSizeX() const {
        return stepSizeX;
    }

    double Grid::getStepSizeY() const {
        return stepSizeY;
    }

}
