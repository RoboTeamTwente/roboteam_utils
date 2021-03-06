cmake_minimum_required(VERSION 3.10)
project(roboteam_utils VERSION 0.1 DESCRIPTION "utils for Roboteam Twente")

option(CODE_COVERAGE "Build for coverage tests" OFF)
function(target_add_coverage_flags TARGET)
    target_compile_options(${TARGET} PUBLIC
            -O0
            -g
            --coverage
            )
endfunction()

add_subdirectory(include/roboteam_utils/networking)

add_library(roboteam_utils STATIC
        src/Polygon.cpp
        include/roboteam_utils/Polygon.h
        src/Line.cpp
        include/roboteam_utils/Line.h
        src/LineSegment.cpp
        include/roboteam_utils/LineSegment.h
        src/Vector2.cpp
        include/roboteam_utils/Vector2.h
        src/Angle.cpp
        include/roboteam_utils/Angle.h
        src/Position.cpp
        include/roboteam_utils/Position.h
        src/Mathematics.cpp
        include/roboteam_utils/Mathematics.h
        #        src/Cone.cpp
        #        include/roboteam_utils/Cone.h
        src/normalize.cpp
        include/roboteam_utils/normalize.h
        include/roboteam_utils/Hungarian.h
        src/Hungarian.cpp
        src/Arc.cpp
        include/roboteam_utils/Arc.h
        src/Timer.cpp
        include/roboteam_utils/Timer.h
        include/roboteam_utils/type_traits.h
        #include/roboteam_utils/BiMap.h
        include/roboteam_utils/Definitions.h
        include/roboteam_utils/Statistics.h
        include/roboteam_utils/Print.h
        src/Rectangle.cpp
        include/roboteam_utils/Rectangle.h
        src/Circle.cpp
        include/roboteam_utils/Circle.h
        src/pid.cpp
        include/roboteam_utils/pid.h
        #src/Triangle.cpp
        #include/roboteam_utils/Triangle.h
        src/Tube.cpp
        include/roboteam_utils/Tube.h
        src/Time.cpp
        include/roboteam_utils/Time.h
        src/Random.cpp
        include/roboteam_utils/Random.h
        src/HalfLine.cpp
        include/roboteam_utils/HalfLine.h
        src/Grid.cpp
        include/roboteam_utils/Grid.h
        src/Shadow.cpp
        include/roboteam_utils/Shadow.h
        include/roboteam_utils/containers/circular_buffer.h
        )


target_include_directories(roboteam_utils
        INTERFACE include
        PRIVATE include/roboteam_utils
        PRIVATE src
        )

target_link_libraries(roboteam_utils
        PUBLIC roboteam_proto
        PUBLIC networking
        )

target_compile_options(roboteam_utils PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
        -Wno-unused-function
        -Wno-deprecated-declarations
        -Wno-comment
        -Wsign-compare
        -g
        )
set_target_properties(roboteam_utils PROPERTIES
        CMAKE_CXX_STANDARD 20
        CMAKE_CXX_STANDARD_REQUIRED 1
        )
add_executable(utils_tests
        test/main.cpp
        test/AngleTest.cpp
        test/ArcTest.cpp
        #test/BiMapTest.cpp
        test/LineTest.cpp
        test/LineIntersectionTest.cpp
        test/LineProjectionTest.cpp
        test/CircleTest.cpp
        test/normaliseTest.cpp
        test/PolygonTest.cpp
        test/PositionTest.cpp
        test/Vector2Test.cpp
        test/RectangleTest.cpp
        test/HungarianTest.cpp
        #test/TriangleTest.cpp
        test/TubeTest.cpp
        test/TimeTest.cpp
        test/RandomTest.cpp
        test/StateMachineTest.cpp
        test/GridTest.cpp
        test/StaticVectorTest.cpp
        test/ShadowTest.cpp
        test/CircularBufferTest.cpp
        test/PubSubTest.cpp
        )

target_link_libraries(utils_tests
        PRIVATE roboteam_utils
        PRIVATE gtest
        )
if(CODE_COVERAGE)
    target_add_coverage_flags(roboteam_utils)
    target_add_coverage_flags(networking)
    target_add_coverage_flags(utils_tests)
    target_link_libraries(utils_tests
            PRIVATE --coverage)

endif(CODE_COVERAGE)
