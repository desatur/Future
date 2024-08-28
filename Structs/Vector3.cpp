#include <cmath>

struct Vector3 {
    float x, y, z;

    Vector3(float x = 0, float y = 0, float z = 0) { // Ctor
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // Magnitude of the vector
    float magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Normalized vector
    Vector3 normalized() const {
        float mag = magnitude();
        if (mag == 0) {
            return Vector3(0, 0, 0);
        }
        return Vector3(x / mag, y / mag, z / mag);
    }

    // Dot product
    float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    Vector3 cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // Addition
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // Subtraction
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // Multiplication by scalar
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // Division by scalar
    Vector3 operator/(float scalar) const {
        if (scalar == 0) {
            // Handle division by zero
            return Vector3(0, 0, 0);
        }
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // Equality check
    bool operator==(const Vector3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    // Inequality check
    bool operator!=(const Vector3& other) const {
        return !(*this == other);
    }
};
