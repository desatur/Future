#include <cmath>

struct Vector2 {
    float x, y;

    Vector2(float x = 0, float y = 0) { // Ctor
        this->x = x;
        this->y = y;
    }

    // Magnitude of the vector
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    // Normalized vector
    Vector2 normalized() const {
        float mag = magnitude();
        if (mag == 0) {
            return Vector2(0, 0);
        }
        return Vector2(x / mag, y / mag);
    }

    // Dot product
    float dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }

    // Addition
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    // Subtraction
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    // Multiplication by scalar
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    // Division by scalar
    Vector2 operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    // Equality check
    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }
};