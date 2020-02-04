#pragma once

#include "Vector2.h"
#include <vector>
#include <string>
#include <iostream>

namespace rtt {

    /**
     * @brief Cone class used for arithmetic
     *
     * Unused as of right now, hence marked maybe unused
     */
    class Cone {
    public:
        /**
         * @brief Construct a new Cone object
         *
         * @param startPoint Start point of the cone
         * @param centerPoint Center point of the cone
         * @param distance Radius of the cone
         */
        Cone(Vector2 startPoint, Vector2 centerPoint, double distance);

        /**
         * @brief Construct a new Cone object
         *
         * @param startPoint Start point of the cone
         * @param sideA Side one of the cone
         * @param sideB Side two of the cone
         */
        Cone(Vector2 startPoint, Vector2 sideA, Vector2 sideB);

        /**
         * @brief Checks whether a point is within this cone
         *
         * @param point Point to be checked
         * @return true True if the point is within the cone
         * @return false If the point is not within the cone
         */
        bool contains(Vector2 point) const noexcept;

        /**
         * @brief Destroy the Cone object
         *
         */
        ~Cone() = default;


        Vector2 center;

        /**
         * @brief Radius of the cone
         *
         */
        double radius;

        /**
         * @brief Angle of the sides of the cone
         *
         */
        double angle;

        /**
         * @brief Side 1 of the cone
         *
         */
        Vector2 side1;

        /**
         * @brief Side 2 of the cone
         *
         */
        Vector2 side2;
    private:
        // Draw drawer;
    };

} // rtt
