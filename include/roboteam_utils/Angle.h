//
// Created by thijs on 28-2-19.
//

#ifndef ANGLE_H
#define ANGLE_H

#include "Mathematics.h"

namespace rtt {

    class Vector2;

/**
 * The Angle class is a modular class on the interval [-PI, PI) that deals with addition, subtractions, distances and comparisons on this scale.
 * @author Created by: Thijs Luttikhuis <br>
 *         Recreated by: Haico Dorenbos
 * @since 2019-02-28
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
         * Construct a new Angle instance by using a double value representing the angle value, which will be directly rescaled.
         * @param angle The given double value. It is allowed to use a value outside the range [-PI, PI).
         */
        Angle(double angle);

        /**
         * Construct a new Angle instance by using the angle of a Vector2 (compared to the origin).
         * @param vec The given Vector2.
         */
        Angle(const rtt::Vector2 &vec);

        /**
         * Get the angle value in the range [-PI, PI).
         * @return The angle value.
         */
        [[nodiscard]] double getAngle() const noexcept;

        /**
         * Compute the shortest absolute angle difference (modular difference) between this Angle and the other Angle.
         * @param other The other Angle.
         * @return A double value in the range [0, PI].
         */
        [[nodiscard]] double shortestAngleDiff(Angle const &other) const noexcept;

        /**
         * Create a new Vector2 using an absolute distance from the origin and this as given Angle.
         * @param length The distance from the origin.
         * @return Vector2 representing this position.
         */
        [[nodiscard]] rtt::Vector2 toVector2(double length = 1.0) const noexcept;

        /**
         * Check if two Angle instances represents the same angle value. This function is protected against double/float rounding issues.
         * @param other The other Angle.
         * @return True if the Angle instances represents the same angle value, false otherwise.
         */
        bool operator==(const Angle &other) const noexcept;

        /**
         * Check if two Angle instances represents the same angle value. This function is protected against double/float rounding issues.
         * @param other The other Angle.
         * @return False if the Angle instances represents the same angle value, true otherwise.
         */
        bool operator!=(const Angle &other) const noexcept;

        /**
         * Compute the addition between this Angle and the other Angle, and directly rescale the angle value.
         * @param other The other Angle.
         * @return A new Angle instance which is the result of the addition.
         */
        Angle operator+(const Angle &other) const noexcept;

        /**
         * Compute the subtraction between this Angle and the other Angle, and directly rescale the angle value.
         * @param other The other Angle.
         * @return A new Angle instance which is the result of the subtraction.
         */
        Angle operator-(const Angle &other) const noexcept;

        /**
         * Add the other Angle to this Angle, and directly rescale the angle value.
         * @param other The other Angle.
         * @return A reference to this updated Angle instance.
         */
        Angle operator+=(const Angle &other) noexcept;

        /**
         * Subtract the other Angle from this Angle, and directly rescale the angle value.
         * @param other The other Angle.
         * @return A reference to this updated Angle instance.
         */
        Angle operator-=(const Angle &other) noexcept;

        /**
         * Set the angle value of this Angle instance, which will be directly rescaled.
         * @param scalar A double value which represent the new angle value. It is allowed to use a value outside the range [-PI, PI).
         * @return A reference to this updated Angle instance.
         */
        Angle &operator=(const double &scalar) noexcept;

    private:
        double angle; // The current angle value, which is a value in the range [-PI, PI).

        /**
         * Rescale the angle value to the range [-PI, PI).
         * @return A reference to this rescaled Angle instance.
         */
        Angle constrain() noexcept;
    };

} // rtt

#endif //ANGLE_H
