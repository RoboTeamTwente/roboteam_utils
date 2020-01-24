#include <gtest/gtest.h>
#include <cstdio>
#include "roboteam_utils/Optimization.h"

namespace rtt {

TEST(OptimizationTests, linear) {
    auto func = [](double x) {
        double t = x - 4;
        return -(t * t);
    };
    // func is optimal at x=4
    ASSERT_DOUBLE_EQ(4.0, optimizeLinear(0, 10, 5, 50, func));
}

}  // namespace rtt