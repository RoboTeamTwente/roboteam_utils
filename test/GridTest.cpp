//
// Created by jesse on 18-05-20.
//

//
// Created by rolf on 22-01-20.
//

#include <gtest/gtest.h>
#include <roboteam_utils/Grid.h>

namespace rtt{

    TEST(Grid, numStepsTest){
        Grid grid = Grid(0, 0, 1, 1, 4, 4);
        auto sizeOfGrid = 0;
        for (auto nestedPoints : grid.getPoints()) {
            sizeOfGrid += nestedPoints.size();
        }
        EXPECT_EQ(sizeOfGrid, 16);

    }



}
