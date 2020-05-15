//
// Created by thijs on 28-2-19.
//

#ifndef ANGLE_H
#define ANGLE_H

#include "Mathematics.h"

namespace rtt {

    class Vector2;

/**
 * @brief Angle class, mostly used for angle calculation
 * 
 */
    class Angle {
    public:
        /**
         * @brief Default constructs an Angle
         * sets angle to 0 and epsilon to 0.00001
         */
        Angle() = default;

        /**
         * @brief Copy constructor
         */
        Angle(const Angle &copy) = default;

        /**
         * @brief Construct a new Angle object
         *
         * @param angle Angle to set the initial angle to
         */
        Angle(double angle);

        /**
         * @brief Construct a new Angle object from an rtt::Vector2
         *
         * @param vec vector to construct from
         */
        Angle(const rtt::Vector2 &vec);

        /**
         * @brief Get the Angle as double
         *
         * @return double The angle
         */
        [[nodiscard]] double getAngle() const noexcept;

        /**
         * @brief Gets the angleDiff of the shortest angle (*this vs other)
         *
         * @param other Other angle to get from
         * @return double
         */
        [[nodiscard]] double shortestAngleDiff(Angle const &other) const noexcept;

        /**
         * @brief Converts the current Angle to a Vector2, does not consume
         *
         * @param length Length of the vector
         * @return rtt::Vector2 The new angle representation
         */
        [[nodiscard]] rtt::Vector2 toVector2(double length = 1.0) const noexcept;

        /**
         * @brief Compares two angles against each other
         *
         * @param other Rhs angle
         * @return true If this->angle - other.angle < epsilon
         * @return false if it's larger
         */
        bool operator==(const Angle &other) const noexcept;

        /**
         * @brief Not equals operator
         *
         * @param other Other angle to compare against
         * @return bool !(*this == other)
         */
        bool operator!=(const Angle &other) const noexcept;

        /**
         * @brief Smaller than operator
         *
         * @param other Other angle to compare against
         * @return true If `this` is smaller than `other`
         * @return false If `other` is bigger or equal to `this`
         */
        bool operator<(const Angle &other) const noexcept;

        /**
         * @brief Combines two angles
         *
         * @param other Other angle
         * @return Angle this->angle + other.angle
         */
        Angle operator+(const Angle &other) const noexcept;

        /**
         * @brief Subtracts two angles
         *
         * @param other Angle to subtract
         * @return Angle this->angle - other.angle
         */
        Angle operator-(const Angle &other) const noexcept;

        /**
         * @brief Sets the current angle equal to`this->angle + other.angle`
         *
         * @param other Other angle to add to `this`
         * @return Angle A copy of `*this`
         */
        Angle operator+=(const Angle &other) noexcept;

        /**
         * @brief Sets the current angle equal to `this->angle - other.angle`
         *
         * @param other Other angle to subtract from `this`
         * @return Angle A copy of `*this`
         */
        Angle operator-=(const Angle &other) noexcept;

        /**
         * @brief Copy assignment operator
         *
         * Explicitly constraints.
         *
         * @param scalar Scalar to set `this->angle` to
         */
        Angle &operator=(const double &scalar) noexcept;

        /**
         * @brief Convert the Angle to a double.
         *
         * TODO: explicit
         *
         * @return double `this->angle`
         */
        operator double() const noexcept;

    private:
        /**
         * @brief Current angle stored
         */
        double angle;

        /**
         * @brief Constrains the angle between 0 and 2 pi
         *
         * @return Angle A copy of `*this`
         */
        Angle constrain() noexcept;
    };

} // rtt

#endif //ANGLE_H
