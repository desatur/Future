#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

struct Vector3 {
    float x, y, z;

    Vector3(float x = 0, float y = 0, float z = 0); // Constructor

    // Magnitude of the vector
    float magnitude() const;

    // Normalized vector
    Vector3 normalized() const;

    // Dot product
    float dot(const Vector3& other) const;

    // Cross product
    Vector3 cross(const Vector3& other) const;

    // Addition
    Vector3 operator+(const Vector3& other) const;

    // Subtraction
    Vector3 operator-(const Vector3& other) const;

    // Multiplication by scalar
    Vector3 operator*(float scalar) const;

    // Division by scalar
    Vector3 operator/(float scalar) const;

    // Equality check
    bool operator==(const Vector3& other) const;

    // Inequality check
    bool operator!=(const Vector3& other) const;
};

#endif // VECTOR3_H
