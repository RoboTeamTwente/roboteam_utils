//
// Created by rolf on 19-4-19.
//

#include <gtest/gtest.h>
#include <math.h>
#include "roboteam_utils/HalfLine.h"
#include "roboteam_utils/Line.h"
#include "roboteam_utils/LineSegment.h"
#include "roboteam_utils/Vector2.h"

using namespace rtt;

TEST(LineTests, lineLengths) {
    Vector2 A(0.0, 0.0), B(2.0, 0.0), C(1.0, 2.0);
    LineSegment D(A, B);
    LineSegment E(A, C);
    LineSegment F(B, C);
    EXPECT_DOUBLE_EQ(D.length(), 2.0);
    EXPECT_DOUBLE_EQ(D.length2(), 4.0);
    EXPECT_DOUBLE_EQ(E.length(), sqrt(5));
    EXPECT_DOUBLE_EQ(E.length2(), 5.0);
    EXPECT_DOUBLE_EQ(F.length(), sqrt(5));
    EXPECT_DOUBLE_EQ(F.length2(), 5.0);
}
TEST(LineTests, distanceToLine) {
    Vector2 A(0.0, 0.0), B(2.0, 2.0);
    Vector2 point1(2.0, 0.0), point2(4.0, 6.0);
    Line l1(A, B);
    LineSegment l2(A, B);

    EXPECT_EQ(l1.distanceToLine(point1), sqrt(2.0));
    EXPECT_EQ(l2.distanceToLine(point1), sqrt(2.0));
    EXPECT_EQ(l1.distanceToLine(point2), sqrt(2.0));
    EXPECT_EQ(l2.distanceToLine(point2), sqrt(20.0));

    Vector2 shouldProj1(1.0, 1.0), shouldProj2(5.0, 5.0);
    EXPECT_EQ(l1.project(point1), shouldProj1);
    EXPECT_EQ(l2.project(point1), shouldProj1);
    EXPECT_EQ(l1.project(point2), shouldProj2);
    EXPECT_EQ(l2.project(point2), B);
}
TEST(LineTests, pointOnLine) {
    Vector2 A(1.0, 1.0), B(3.0, 1.0), C(1.0, 3.0), D(3.0, 3.0);
    LineSegment ls1(A, B), ls2(A, C), ls3(A, D);
    /*
    Vector2 point1(2.0, 1.0), point2(4.0, 1.0);
    Line l1(A, B), l2(A, C), l3(A, D);
    EXPECT_TRUE(l1.isOnLine(point1));
    EXPECT_TRUE(l1.isOnLine(point2));
    EXPECT_TRUE(ls1.isOnLine(point1));
    EXPECT_FALSE(ls1.isOnLine(point2));

    // check the original points
    EXPECT_TRUE(l1.isOnLine(B));
    EXPECT_TRUE(ls1.isOnLine(B));
    EXPECT_TRUE(l1.isOnLine(A));
    EXPECT_TRUE(ls1.isOnLine(A));

    Vector2 point3(1.0, 2.0), point4(1.0, 4.0);
    EXPECT_TRUE(l2.isOnLine(point3));
    EXPECT_TRUE(l2.isOnLine(point4));
    EXPECT_TRUE(ls2.isOnLine(point3));
    EXPECT_FALSE(ls2.isOnLine(point4));  // check the original points

    EXPECT_TRUE(l2.isOnLine(C));
    EXPECT_TRUE(ls2.isOnLine(C));
    EXPECT_TRUE(l2.isOnLine(A));
    EXPECT_TRUE(ls2.isOnLine(A));
    */
    Vector2 point5(2.0, 2.0), point6(4.0, 4.0);

    /*
    EXPECT_TRUE(l3.isOnLine(point5));
    EXPECT_TRUE(l3.isOnLine(point6));
    EXPECT_TRUE(ls3.isOnLine(point5));
    EXPECT_FALSE(ls3.isOnLine(point6));  // check the original points

    EXPECT_TRUE(l3.isOnLine(D));
    EXPECT_TRUE(ls3.isOnLine(D));
    EXPECT_TRUE(l3.isOnLine(A));
    EXPECT_TRUE(ls3.isOnLine(A));
    */

    LineSegment degenerate(point5,point5);
    EXPECT_FALSE(degenerate.isOnLine(point6));
    /*
    Line degenLine(degenerate);
    EXPECT_FALSE(degenLine.isOnLine(point6));
    */
}

TEST(LineTests, IntersectionsDifferentTypes) {
    Vector2 P1(0.0, 0.0), P2(2.0, 2.0), P3(2.0, 0.0), P4(0.0, 2.0);
    Vector2 middle(1.0, 1.0);
    Line L1(P1, P2), L2(P3, P4);
    LineSegment LS1(P1, P2), LS2(P3, P4);

    // no special things, just normal intersection. Should work as expected
    // ASSERT_NE(LS1.intersects(L2), std::nullopt);
    // ASSERT_EQ(*LS1.intersects(L2), middle);
    // ASSERT_NE(L2.intersects(LS1), std::nullopt);
    // ASSERT_EQ(*L2.intersects(LS1), middle);
    // ASSERT_NE(LS2.intersects(L1), std::nullopt);
    // ASSERT_EQ(*LS2.intersects(L1), middle);
    // ASSERT_NE(L1.intersects(LS2), std::nullopt);
    // ASSERT_EQ(*L1.intersects(LS2), middle);

    // EXPECT_TRUE(LS1.doesIntersect(L2));
    // EXPECT_TRUE(LS2.doesIntersect(L1));
    // EXPECT_TRUE(L2.doesIntersect(LS1));
    // EXPECT_TRUE(L1.doesIntersect(LS2));

    // Lies in the extension of the line
    Vector2 R1(0.0, 0.0), R2(1.0, 0.0), R3(0.0, -4.0), R4(8.0, 4.0);
    Line A1(R1, R2), A2(R3, R4);
    LineSegment AS1(R1, R2), AS2(R3, R4);

    // EXPECT_EQ(AS1.intersects(A2), std::nullopt);
    // EXPECT_FALSE(AS1.doesIntersect(A2));
    // EXPECT_NE(A1.intersects(AS2), std::nullopt);
    // EXPECT_TRUE(A1.doesIntersect(AS2));
    // EXPECT_EQ(*A1.intersects(AS2), Vector2(4.0, 0.0));

    // edge cases
    Vector2 R5(1.0, 3.0), R6(1.0, -1.0), R7(2.0, 0.0), R8(3.0, 0.0);
    Line A3(R5, R6), A4(R2, R7), A5(R7, R8);
    LineSegment AS3(R5, R6), AS4(R2, R7), AS5(R7, R8);

    ASSERT_NE(AS1.intersects(AS4), std::nullopt);
    EXPECT_TRUE(AS1.doesIntersect(AS4));
    EXPECT_EQ(*AS1.intersects(AS4), R2);
}

TEST(LineTests, Intersections) {
    /* In this test case we test the different intersection methods in different line classes: Line, LineSegment and HalfLine. For these methods we want to cover 3 type of lines:
     * vertical line (does not change in x direction), horizontal line (does not change in y direction), arbitrary other line (does change in both x and y direction). This is to
     * test cases where there could be a possibility of division by zero. Furthermore for the non-parallel test cases we create 3 classes based on the relative position where they
     * intersect (or do not intersect): t < 0, 0 <= t <= 1, 1 < t. We extend these test cases with boundary value analysis, but for t is (minus) infinity we use a very small and
     * very large number (we expect intersections to fail for FLT_MAX and -FLT_MAX). Moreover for parallel test cases we create 3 classes based on the LineSegment interpretation:
     * 'Equal': both LineSegment interpretation are equal, 'Subset': one of the LineSegments interpretations is a subset of the other, 'Overlap': both LineSegments interpretations
     * have a shared part, but non of them is a subset of the other one, 'Distinct': both LineSegments do not intersect, but have a shared finite LineSegment where both ar subsets
     * of, 'Different': both LineSegments do not intersect and do not have a shared infinite Line where both are subsets of. Furthermore create a test case for two LineSegments
     * that are 'Equal' points and that are 'Different' points.
     */
    double EPSILON = 1e-2; // Small difference that is still significant enough to really change a Vector2 position.

    // Non-parallel test case with horizontal line and vertical line, where intersection happens for the first line at 0 <= t <= 1 and for the second at t = -EPSILON.
    Vector2 start1(3.0, 2.0), end1(6.0, 2.0), start2(4.0, 2 + EPSILON), end2(4.0, 5.0), intersection(4.0, 2.0);
    Line line1(start1, end1), line2(start2, end2);
    HalfLine halfLine(start1, end1);
    LineSegment lineSegment1(start1, end1), lineSegment2(start2, end2);
    std::optional<Vector2> result = halfLine.intersect(line2);
    EXPECT_EQ(result.value(), intersection);
    result = line1.intersect(line2);
    EXPECT_EQ(result.value(), intersection);
    result = Line::intersect(start1, end1, start2, end2);
    EXPECT_EQ(result.value(), intersection);
    EXPECT_FALSE(lineSegment1.doesIntersect(lineSegment2));
    result = lineSegment1.intersects(lineSegment2);
    EXPECT_FALSE(result.has_value());
    std::vector<Vector2> result2 = lineSegment1.multiIntersect(lineSegment2);
    EXPECT_EQ(result2.size(), 0);

    // Non-parallel test case with two arbitrary lines, where intersection happens for the first line at t = 1 + EPSILON and for the second at 0 <= t <= 1.
    start1 = {10.0, -6.0}, end1 = {1.0, 0.0}, start2 = {0.0 + EPSILON, -2.0 + 2 * EPSILON / 3}, end2 = {3.0 + EPSILON, 4.0 + 2 * EPSILON / 3},
    intersection = {1.0 + EPSILON, 2 * EPSILON / 3};
    line1 = Line(start1, end1), line2 = Line(start2, end2); halfLine = HalfLine(start1, end1);
    lineSegment1 = LineSegment(start1, end1), lineSegment2 = LineSegment(start2, end2);
    result = halfLine.intersect(line2);
    EXPECT_EQ(result.value(), intersection);
    result = line1.intersect(line2);
    EXPECT_EQ(result.value(), intersection);
    result = Line::intersect(start1, end1, start2, end2);
    EXPECT_EQ(result.value(), intersection);
    EXPECT_FALSE(lineSegment1.doesIntersect(lineSegment2));
    result = lineSegment1.intersects(lineSegment2);
    EXPECT_FALSE(result.has_value());
    result2 = lineSegment1.multiIntersect(lineSegment2);
    EXPECT_EQ(result2.size(), 0);

    // Non-parallel test case with horizontal line and arbitrary line, where intersection happens for the first line at t = -EPSILON and for the second at t = LARGE.
    start1 = {-2.0 + EPSILON, 10001.0}, end1 = {8.0, 10001.0}, start2 = {-502.0, -9999.0}, end2 = {-500.0, -9991.0}, intersection = {-2.0, 10001.0};
    line1 = Line(start1, end1), line2 = Line(start2, end2); halfLine = HalfLine(start1, end1);
    lineSegment1 = LineSegment(start1, end1), lineSegment2 = LineSegment(start2, end2);
    result = halfLine.intersect(line2);
    EXPECT_FALSE(result.has_value());
    result = line1.intersect(line2);
    EXPECT_EQ(result.value(), intersection);
    result = Line::intersect(start1, end1, start2, end2);
    EXPECT_EQ(result.value(), intersection);
    EXPECT_FALSE(lineSegment1.doesIntersect(lineSegment2));
    result = lineSegment1.intersects(lineSegment2);
    EXPECT_FALSE(result.has_value());
    result2 = lineSegment1.multiIntersect(lineSegment2);
    EXPECT_EQ(result2.size(), 0);

    // Non-parallel test case with arbitrary line and vertical, where intersection happens for the first line at t = 1 and for the second at t = 0.
    start1 = {-1.0, -4.0}, end1 = {3.0, 8.0}, start2 = {3.0, 8.0}, end2 = {3.0, 6.5}, intersection = {3.0, 8.0};
    line1 = Line(start1, end1), line2 = Line(start2, end2); halfLine = HalfLine(start1, end1);
    lineSegment1 = LineSegment(start1, end1), lineSegment2 = LineSegment(start2, end2);
    result = halfLine.intersect(line2);
    EXPECT_EQ(result.value(), intersection);
    result = line1.intersect(line2);
    EXPECT_EQ(result.value(), intersection);
    result = Line::intersect(start1, end1, start2, end2);
    EXPECT_EQ(result.value(), intersection);
    EXPECT_TRUE(lineSegment1.doesIntersect(lineSegment2));
    result = lineSegment1.intersects(lineSegment2);
    EXPECT_EQ(result.value(), intersection);
    result2 = lineSegment1.multiIntersect(lineSegment2);
    EXPECT_EQ(result2.size(), 1);
    EXPECT_EQ(result2[0], intersection);

    // Non-parallel test case with two arbitrary lines, where intersection happens for the first line at t = -LARGE and for the second at t = -LARGE.
    start1 = {8.0, 49.8}, end1 = {38.0, 50.0}, start2 = {-22.0, -10.0}, end2 = {8.0, -9.9}, intersection = {-17902.0, -1798.0};
    line1 = Line(start1, end1), line2 = Line(start2, end2); halfLine = HalfLine(start1, end1);
    lineSegment1 = LineSegment(start1, end1), lineSegment2 = LineSegment(start2, end2);
    result = halfLine.intersect(line2);
    EXPECT_FALSE(result.has_value());
    result = line1.intersect(line2);
    EXPECT_EQ(result.value(), intersection);
    result = Line::intersect(start1, end1, start2, end2);
    EXPECT_EQ(result.value(), intersection);
    EXPECT_FALSE(lineSegment1.doesIntersect(lineSegment2));
    result = lineSegment1.intersects(lineSegment2);
    EXPECT_FALSE(result.has_value());
    result2 = lineSegment1.multiIntersect(lineSegment2);
    EXPECT_EQ(result2.size(), 0);

    // Non-parallel test case a vertical and horizontal line, where intersection happens for the first line at t = LARGE and for the second at t = 1 + EPSILON.
    start1 = {-10.0, 10000.0}, end1 = {-10.0, 9999.9}, start2 = {20.0, 5.0}, end2 = {-10.0 + EPSILON, 5.0}, intersection = {-10.0, 5.0};
    line1 = Line(start1, end1), line2 = Line(start2, end2); halfLine = HalfLine(start1, end1);
    lineSegment1 = LineSegment(start1, end1), lineSegment2 = LineSegment(start2, end2);
    result = halfLine.intersect(line2);
    EXPECT_EQ(result.value(), intersection);
    result = line1.intersect(line2);
    EXPECT_EQ(result.value(), intersection);
    result = Line::intersect(start1, end1, start2, end2);
    EXPECT_EQ(result.value(), intersection);
    EXPECT_FALSE(lineSegment1.doesIntersect(lineSegment2));
    result = lineSegment1.intersects(lineSegment2);
    EXPECT_FALSE(result.has_value());
    result2 = lineSegment1.multiIntersect(lineSegment2);
    EXPECT_EQ(result2.size(), 0);

    // Non-parallel test case a vertical line and arbitrary line, where intersection happens for the first line at t = 0 and for the second at 0 <= t <= 1.
    start1 = {6.0, -2.0}, end1 = {6.0, -500.0}, start2 = {9.0, 1.0}, end2 = {3.0, -5.0}, intersection = {6.0, -2.0};
    line1 = Line(start1, end1), line2 = Line(start2, end2); halfLine = HalfLine(start1, end1);
    lineSegment1 = LineSegment(start1, end1), lineSegment2 = LineSegment(start2, end2);
    result = halfLine.intersect(line2);
    EXPECT_EQ(result.value(), intersection);
    result = line1.intersect(line2);
    EXPECT_EQ(result.value(), intersection);
    result = Line::intersect(start1, end1, start2, end2);
    EXPECT_EQ(result.value(), intersection);
    EXPECT_TRUE(lineSegment1.doesIntersect(lineSegment2));
    result = lineSegment1.intersects(lineSegment2);
    EXPECT_EQ(result.value(), intersection);
    result2 = lineSegment1.multiIntersect(lineSegment2);
    EXPECT_EQ(result2.size(), 1);
    EXPECT_EQ(result2[0], intersection);

    // Parallel test case with two 'Equal' arbitrary lines.
    start1 = {-1000.0, -800.0}, end1 = {-200.0, -400.0}, start2 = {-200.0, -400.0}, end2 = {-1000.0, -800.0};
    line1 = Line(start1, end1), line2 = Line(start2, end2); halfLine = HalfLine(start1, end1);
    lineSegment1 = LineSegment(start1, end1), lineSegment2 = LineSegment(start2, end2);
    result = halfLine.intersect(line2);
    EXPECT_FALSE(result.has_value());
    result = line1.intersect(line2);
    EXPECT_FALSE(result.has_value());
    result = Line::intersect(start1, end1, start2, end2);
    EXPECT_FALSE(result.has_value());
    EXPECT_TRUE(lineSegment1.doesIntersect(lineSegment2));
    result = lineSegment1.intersects(lineSegment2);
    EXPECT_EQ(result.value(), start1);
    result2 = lineSegment1.multiIntersect(lineSegment2);
    EXPECT_EQ(result2.size(), 2);
    EXPECT_EQ(result2[0], end1);
    EXPECT_EQ(result2[1], start1);

    // Parallel test case where the first vertical line is a subset of the second vertical line.
    start1 = {5.0, 3.0}, end1 = {5.0, 6.0}, start2 = {5.0, 12.0}, end2 = {5.0, 3.0};
    line1 = Line(start1, end1), line2 = Line(start2, end2); halfLine = HalfLine(start1, end1);
    lineSegment1 = LineSegment(start1, end1), lineSegment2 = LineSegment(start2, end2);
    result = halfLine.intersect(line2);
    EXPECT_FALSE(result.has_value());
    result = line1.intersect(line2);
    EXPECT_FALSE(result.has_value());
    result = Line::intersect(start1, end1, start2, end2);
    EXPECT_FALSE(result.has_value());
    EXPECT_TRUE(lineSegment1.doesIntersect(lineSegment2));
    result = lineSegment1.intersects(lineSegment2);
    EXPECT_EQ(result.value(), start1);
    result2 = lineSegment1.multiIntersect(lineSegment2);
    EXPECT_EQ(result2.size(), 2);
    EXPECT_EQ(result2[0], start1);
    EXPECT_EQ(result2[1], end1);

    // Parallel test case where the second line is actually a point that lies at the first horizontal line.
    start1 = {15.0, -7.0}, end1 = {3.0, -7.0}, start2 = {11.0, -7.0}, end2 = {11.0, -7.0};
    lineSegment1 = LineSegment(start1, end1), lineSegment2 = LineSegment(start2, end2);
    result = Line::intersect(start1, end1, start2, end2);
    EXPECT_FALSE(result.has_value());
    EXPECT_TRUE(lineSegment1.doesIntersect(lineSegment2));
    result = lineSegment1.intersects(lineSegment2);
    EXPECT_EQ(result.value(), start2);
    result2 = lineSegment1.multiIntersect(lineSegment2);
    EXPECT_EQ(result2.size(), 1);
    EXPECT_EQ(result2[0], start2);

    // Parallel test case with two 'Distinct' horizontal lines.
    start1 = {-4.0, 10.0}, end1 = {-3.0, 35.0}, start2 = {-3.0, 35.0}, end2 = {-1.0, 85.0};
    line1 = Line(start1, end1), line2 = Line(start2, end2); halfLine = HalfLine(start1, end1);
    lineSegment1 = LineSegment(start1, end1), lineSegment2 = LineSegment(start2, end2);
    result = halfLine.intersect(line2);
    EXPECT_FALSE(result.has_value());
    result = line1.intersect(line2);
    EXPECT_FALSE(result.has_value());
    result = Line::intersect(start1, end1, start2, end2);
    EXPECT_FALSE(result.has_value());
    EXPECT_TRUE(lineSegment1.doesIntersect(lineSegment2));
    result = lineSegment1.intersects(lineSegment2);
    EXPECT_EQ(result.value(), end1);
    result2 = lineSegment1.multiIntersect(lineSegment2);
    EXPECT_EQ(result2.size(), 1);
    EXPECT_EQ(result2[0], end1);

    // Parallel test case with two arbitrary 'Overlap' lines.
    start1 = {-4.0, 10.0}, end1 = {-3.0, 35.0}, start2 = {-3.0, 35.0}, end2 = {-1.0, 85.0};
    line1 = Line(start1, end1), line2 = Line(start2, end2); halfLine = HalfLine(start1, end1);
    lineSegment1 = LineSegment(start1, end1), lineSegment2 = LineSegment(start2, end2);
    result = halfLine.intersect(line2);
    EXPECT_FALSE(result.has_value());
    result = line1.intersect(line2);
    EXPECT_FALSE(result.has_value());
    result = Line::intersect(start1, end1, start2, end2);
    EXPECT_FALSE(result.has_value());
    EXPECT_TRUE(lineSegment1.doesIntersect(lineSegment2));
    result = lineSegment1.intersects(lineSegment2);
    EXPECT_EQ(result.value(), end1);
    result2 = lineSegment1.multiIntersect(lineSegment2);
    EXPECT_EQ(result2.size(), 1);
    EXPECT_EQ(result2[0], end1);

    // Parallel test case with two 'Different' vertical lines.
    start1 = {10.0, -5.0}, end1 = {10.0, -15.0}, start2 = {10.0 - EPSILON, -5.0}, end2 = {10.0 - EPSILON, -15.0};
    line1 = Line(start1, end1), line2 = Line(start2, end2); halfLine = HalfLine(start1, end1);
    lineSegment1 = LineSegment(start1, end1), lineSegment2 = LineSegment(start2, end2);
    result = halfLine.intersect(line2);
    EXPECT_FALSE(result.has_value());
    result = line1.intersect(line2);
    EXPECT_FALSE(result.has_value());
    result = Line::intersect(start1, end1, start2, end2);
    EXPECT_FALSE(result.has_value());
    EXPECT_FALSE(lineSegment1.doesIntersect(lineSegment2));
    result = lineSegment1.intersects(lineSegment2);
    EXPECT_FALSE(result.has_value());
    result2 = lineSegment1.multiIntersect(lineSegment2);
    EXPECT_EQ(result2.size(), 0);

    // Test case with two lines that are actually 'Equal' points.
    start1 = {0.0, 0.0}, end1 = {0.0, 0.0}, start2 = {0.0, 0.0}, end2 = {0.0, 0.0};
    lineSegment1 = LineSegment(start1, end1), lineSegment2 = LineSegment(start2, end2);
    result = Line::intersect(start1, end1, start2, end2);
    EXPECT_FALSE(result.has_value());
    EXPECT_TRUE(lineSegment1.doesIntersect(lineSegment2));
    result = lineSegment1.intersects(lineSegment2);
    EXPECT_EQ(result.value(), start1);
    result2 = lineSegment1.multiIntersect(lineSegment2);
    EXPECT_EQ(result2.size(), 1);
    EXPECT_EQ(result2[0], start1);

    // Test case with two lines that are actually 'Different' points.
    start1 = {6.0 + EPSILON, 6.0}, end1 = {6.0 + EPSILON, 6.0}, start2 = {6.0, 6.0}, end2 = {6.0, 6.0};
    lineSegment1 = LineSegment(start1, end1), lineSegment2 = LineSegment(start2, end2);
    result = Line::intersect(start1, end1, start2, end2);
    EXPECT_FALSE(result.has_value());
    EXPECT_FALSE(lineSegment1.doesIntersect(lineSegment2));
    result = lineSegment1.intersects(lineSegment2);
    EXPECT_FALSE(result.has_value());
    result2 = lineSegment1.multiIntersect(lineSegment2);
    EXPECT_EQ(result2.size(), 0);
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
 * These test cases are outdated or test dead functionality. Remove this tag if you use this code and make sure to remove this tag at other places as well that will become alive
 * by using this code.
 * Do not read/document/redesign/analyse/test/optimize/etc. any of this code, because it is a waste of your time! This code was not removed or placed at another branch, because
 * other software developers are very attached to this code and are afraid that this code might be used at some day (but I think it won't be used at all and should be removed).
 */

/*
TEST(LineTests, pointOnLine) {
    Vector2 A(1.0, 1.0), B(3.0, 1.0), C(1.0, 3.0), D(3.0, 3.0);
    LineSegment ls1(A, B), ls2(A, C), ls3(A, D);

    Vector2 point1(2.0, 1.0), point2(4.0, 1.0);
    Line l1(A, B), l2(A, C), l3(A, D);
    EXPECT_TRUE(l1.isOnLine(point1));
    EXPECT_TRUE(l1.isOnLine(point2));
    EXPECT_TRUE(ls1.isOnLine(point1));
    EXPECT_FALSE(ls1.isOnLine(point2));

    // check the original points
    EXPECT_TRUE(l1.isOnLine(B));
    EXPECT_TRUE(ls1.isOnLine(B));
    EXPECT_TRUE(l1.isOnLine(A));
    EXPECT_TRUE(ls1.isOnLine(A));

    Vector2 point3(1.0, 2.0), point4(1.0, 4.0);
    EXPECT_TRUE(l2.isOnLine(point3));
    EXPECT_TRUE(l2.isOnLine(point4));
    EXPECT_TRUE(ls2.isOnLine(point3));
    EXPECT_FALSE(ls2.isOnLine(point4));  // check the original points

    EXPECT_TRUE(l2.isOnLine(C));
    EXPECT_TRUE(ls2.isOnLine(C));
    EXPECT_TRUE(l2.isOnLine(A));
    EXPECT_TRUE(ls2.isOnLine(A));

    Vector2 point5(2.0, 2.0), point6(4.0, 4.0);

    EXPECT_TRUE(l3.isOnLine(point5));
    EXPECT_TRUE(l3.isOnLine(point6));
    EXPECT_TRUE(ls3.isOnLine(point5));
    EXPECT_FALSE(ls3.isOnLine(point6));  // check the original points

    EXPECT_TRUE(l3.isOnLine(D));
    EXPECT_TRUE(ls3.isOnLine(D));
    EXPECT_TRUE(l3.isOnLine(A));
    EXPECT_TRUE(ls3.isOnLine(A));

    LineSegment degenerate(point5,point5);
    EXPECT_FALSE(degenerate.isOnLine(point6));

    Line degenLine(degenerate);
    EXPECT_FALSE(degenLine.isOnLine(point6));
}

TEST(LineTests, IntersectionsDifferentTypes) {
    Vector2 P1(0.0, 0.0), P2(2.0, 2.0), P3(2.0, 0.0), P4(0.0, 2.0);
    Vector2 middle(1.0, 1.0);
    Line L1(P1, P2), L2(P3, P4);
    LineSegment LS1(P1, P2), LS2(P3, P4);

    // no special things, just normal intersection. Should work as expected
    // ASSERT_NE(LS1.intersects(L2), std::nullopt);
    // ASSERT_EQ(*LS1.intersects(L2), middle);
    // ASSERT_NE(L2.intersects(LS1), std::nullopt);
    // ASSERT_EQ(*L2.intersects(LS1), middle);
    // ASSERT_NE(LS2.intersects(L1), std::nullopt);
    // ASSERT_EQ(*LS2.intersects(L1), middle);
    // ASSERT_NE(L1.intersects(LS2), std::nullopt);
    // ASSERT_EQ(*L1.intersects(LS2), middle);

    // EXPECT_TRUE(LS1.doesIntersect(L2));
    // EXPECT_TRUE(LS2.doesIntersect(L1));
    // EXPECT_TRUE(L2.doesIntersect(LS1));
    // EXPECT_TRUE(L1.doesIntersect(LS2));

    // Lies in the extension of the line
    Vector2 R1(0.0, 0.0), R2(1.0, 0.0), R3(0.0, -4.0), R4(8.0, 4.0);
    Line A1(R1, R2), A2(R3, R4);
    LineSegment AS1(R1, R2), AS2(R3, R4);

    // EXPECT_EQ(AS1.intersects(A2), std::nullopt);
    // EXPECT_FALSE(AS1.doesIntersect(A2));
    // EXPECT_NE(A1.intersects(AS2), std::nullopt);
    // EXPECT_TRUE(A1.doesIntersect(AS2));
    // EXPECT_EQ(*A1.intersects(AS2), Vector2(4.0, 0.0));

    // edge cases
    Vector2 R5(1.0, 3.0), R6(1.0, -1.0), R7(2.0, 0.0), R8(3.0, 0.0);
    Line A3(R5, R6), A4(R2, R7), A5(R7, R8);
    LineSegment AS3(R5, R6), AS4(R2, R7), AS5(R7, R8);

    ASSERT_NE(AS1.intersects(AS4), std::nullopt);
    EXPECT_TRUE(AS1.doesIntersect(AS4));
    EXPECT_EQ(*AS1.intersects(AS4), R2);
}

TEST(LineTests, direction) {

    Vector2 v1(0.0, 0.0), v2(1.0, 1.0), v3(0.0, 0.0);
    Line l1(v1, v2), l2(v2, v1), l3(v1, v3);
    Vector2 v4(0.0, 0.0), v5(0.0, 10.0), v6(2.0, 0.0), v7(2.0, 9.0);
    Vector2 v8(2.0, 0.0), v9(3.0, 10.0), v10(0.0 + std::numeric_limits<double>::epsilon(), 10);
    Line l4(v4, v5), l5(v6, v7);
    LineSegment l6(v4, v8), l7(v5, v9);
    Line l8(v4,v10);

    EXPECT_TRUE(l4.isParallel(l5));
    EXPECT_TRUE(l5.isParallel(l4));
    EXPECT_TRUE(l6.isParallel(l7));
    EXPECT_TRUE(l7.isParallel(l6));
    EXPECT_FALSE(l1.isParallel(l4));
    EXPECT_FALSE(l1.isParallel(l5));
    EXPECT_FALSE(l1.isParallel(l6));
    EXPECT_FALSE(l1.isParallel(l7));

    EXPECT_FALSE(l4.isParallel(l6));
    EXPECT_FALSE(l5.isParallel(l6));
    EXPECT_FALSE(l6.isParallel(l4));
    EXPECT_FALSE(l6.isParallel(l5));
    EXPECT_FALSE(l4.isParallel(l7));
    EXPECT_FALSE(l5.isParallel(l7));
    EXPECT_FALSE(l7.isParallel(l4));
    EXPECT_FALSE(l7.isParallel(l5));
    EXPECT_FALSE(l4.isParallel(l8));
}

TEST(LineTests, Intersections) {
    Vector2 P1(0.0, 0.0), P2(1.0, 1.0), P3(4.0, 0.0), P4(0.0, 4.0), P5(4.0, 4.0);
    Line L1(P1, P2), L2(P3, P4), L3(P3, P5), L4(P1, P5), L5(P1, P4);
    LineSegment LS1(P1, P2), LS2(P3, P4), LS3(P3, P5), LS4(P1, P5), LS5(P1, P4);
    Vector2 intersect(2.0, 2.0);

    //Test constructors
    EXPECT_EQ(Line(LS1).start, L1.start);
    EXPECT_EQ(Line(LS1).end, L1.end);
    EXPECT_NE(Line(LS1).start, L2.start);
    EXPECT_NE(Line(LS1).end, L2.end);
    EXPECT_EQ(LineSegment(L1).start, LS1.start);
    EXPECT_EQ(LineSegment(L1).end, LS1.end);

    EXPECT_NE(LineSegment(L1).start, LS2.start);
    EXPECT_NE(LineSegment(L1).end, LS2.end);


    ASSERT_NE(L1.intersects(L2), std::nullopt);
    ASSERT_TRUE(L1.doesIntersect(L2));
    EXPECT_EQ(*L1.intersects(L2), intersect);
    // test converse
    ASSERT_NE(L2.intersects(L1), std::nullopt);
    ASSERT_TRUE(L2.doesIntersect(L1));
    EXPECT_EQ(*L2.intersects(L1), intersect);

    ASSERT_EQ(LS1.intersects(LS2), std::nullopt);
    ASSERT_FALSE(LS1.doesIntersect(LS2));
    // test converse
    ASSERT_EQ(LS2.intersects(LS1), std::nullopt);
    ASSERT_FALSE(LS2.doesIntersect(LS1));

    ASSERT_NE(L2.intersects(L4), std::nullopt);
    ASSERT_TRUE(L2.doesIntersect(L4));
    EXPECT_EQ(*L2.intersects(L4), intersect);
    // test converse
    ASSERT_NE(L4.intersects(L2), std::nullopt);
    ASSERT_TRUE(L4.doesIntersect(L2));
    EXPECT_EQ(*L4.intersects(L2), intersect);

    ASSERT_NE(LS2.intersects(LS4), std::nullopt);
    ASSERT_TRUE(LS2.doesIntersect(LS4));
    EXPECT_EQ(*LS2.intersects(LS4), intersect);
    // test converse
    ASSERT_NE(LS4.intersects(LS2), std::nullopt);
    ASSERT_TRUE(LS4.doesIntersect(LS2));
    EXPECT_EQ(*LS4.intersects(LS2), intersect);

    ASSERT_NE(L3.intersects(L4), std::nullopt);
    ASSERT_TRUE(L3.doesIntersect(L4));
    EXPECT_EQ(*L3.intersects(L4), P5);
    // test converse
    ASSERT_NE(L4.intersects(L3), std::nullopt);
    ASSERT_TRUE(L4.doesIntersect(L3));
    EXPECT_EQ(*L4.intersects(L3), P5);

    ASSERT_NE(LS3.intersects(LS4), std::nullopt);
    ASSERT_TRUE(LS3.doesIntersect(LS4));
    EXPECT_EQ(*LS3.intersects(LS4), P5);
    // test converse
    ASSERT_NE(LS4.intersects(LS3), std::nullopt);
    ASSERT_TRUE(LS4.doesIntersect(LS3));
    EXPECT_EQ(*LS4.intersects(LS3), P5);

    EXPECT_EQ(L3.intersects(L5), std::nullopt);
    EXPECT_FALSE(L3.doesIntersect(L5));
    // test converse
    EXPECT_EQ(L5.intersects(L3), std::nullopt);
    EXPECT_FALSE(L5.doesIntersect(L3));

    EXPECT_EQ(LS3.intersects(LS5), std::nullopt);
    EXPECT_FALSE(LS3.doesIntersect(LS5));
    // test converse
    EXPECT_EQ(LS5.intersects(LS3), std::nullopt);
    EXPECT_FALSE(LS5.doesIntersect(LS3));

    EXPECT_EQ(L2.intersects(LS1), std::nullopt);
    EXPECT_FALSE(L2.doesIntersect(LS1));
}
TEST(LineTests, slopeAndIntercept) {
    Vector2 Av(1.0, 1.0), Bv(2.0, 2.0), Cv(2.0, 3.0), Dv(1.0, 4.0), Ev(2.0, 0.0);
    Line D(Av, Bv), E(Av, Cv), F(Av, Dv), G(Dv, Av), H(Av, Ev);
    Line Dcopy(Bv, Av), Ecopy(Cv, Av), Hcopy(Ev, Av);

    // test normal slopes
    EXPECT_DOUBLE_EQ(D.slope(), 1.0);
    EXPECT_DOUBLE_EQ(E.slope(), 2.0);
    EXPECT_DOUBLE_EQ(H.slope(), -1.0);
    // test vertical lines giving back numeric limits
    EXPECT_DOUBLE_EQ(F.slope(), std::numeric_limits<double>::infinity());
    EXPECT_DOUBLE_EQ(G.slope(), -std::numeric_limits<double>::infinity());
    EXPECT_FALSE(D.isVertical());
    EXPECT_FALSE(E.isVertical());
    EXPECT_FALSE(H.isVertical());
    EXPECT_TRUE(F.isVertical());
    EXPECT_TRUE(G.isVertical());
    // make sure the functions are commutative
    EXPECT_DOUBLE_EQ(D.slope(), Dcopy.slope());
    EXPECT_DOUBLE_EQ(E.slope(), Ecopy.slope());
    EXPECT_DOUBLE_EQ(H.slope(), Hcopy.slope());

    // calculate the intercept for normal cases and check commutativity
    EXPECT_DOUBLE_EQ(D.intercept(), 0.0);
    EXPECT_DOUBLE_EQ(E.intercept(), -1.0);
    EXPECT_DOUBLE_EQ(H.intercept(), 2.0);
    EXPECT_DOUBLE_EQ(D.intercept(), Dcopy.intercept());
    EXPECT_DOUBLE_EQ(E.intercept(), Ecopy.intercept());
    EXPECT_DOUBLE_EQ(H.intercept(), Hcopy.intercept());

    EXPECT_DOUBLE_EQ(F.intercept(), -std::numeric_limits<double>::infinity());
    EXPECT_DOUBLE_EQ(G.intercept(), std::numeric_limits<double>::infinity());

    EXPECT_DOUBLE_EQ(D.coefficients().first, D.slope());
    EXPECT_DOUBLE_EQ(E.coefficients().first, E.slope());
    EXPECT_DOUBLE_EQ(F.coefficients().first, F.slope());
    EXPECT_DOUBLE_EQ(G.coefficients().first, G.slope());
    EXPECT_DOUBLE_EQ(H.coefficients().first, H.slope());
    EXPECT_DOUBLE_EQ(D.coefficients().second, D.intercept());
    EXPECT_DOUBLE_EQ(E.coefficients().second, E.intercept());
    EXPECT_DOUBLE_EQ(F.coefficients().second, F.intercept());
    EXPECT_DOUBLE_EQ(G.coefficients().second, G.intercept());
    EXPECT_DOUBLE_EQ(H.coefficients().second, H.intercept());
}
*/