#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

struct Vector2 {
    float x, y;

    Vector2(float x = 0, float y = 0); // Constructor

    // Magnitude of the vector
    float magnitude() const;

    // Normalized vector
    Vector2 normalized() const;

    // Dot product
    float dot(const Vector2& other) const;

    // Addition
    Vector2 operator+(const Vector2& other) const;

    // Subtraction
    Vector2 operator-(const Vector2& other) const;

    // Multiplication by scalar
    Vector2 operator*(float scalar) const;

    // Division by scalar
    Vector2 operator/(float scalar) const;

    // Equality check
    bool operator==(const Vector2& other) const;
};

#endif // VECTOR2_H
