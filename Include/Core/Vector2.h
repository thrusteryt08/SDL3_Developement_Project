#pragma once
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cassert>

namespace AxionForge {

	// Floating point 2D vector
    class Vector2 {
    public:
        float x = 0;
        float y = 0;
		// Create a 2D vector (0, 0)
        Vector2() { x = 0; y = 0; }
		// Create a 2D vector (x, x)
        explicit Vector2(float x) : x(x), y(x) {}
        explicit Vector2(int x) : x(static_cast<float>(x)), y(static_cast<float>(x)) {}
        // Create a 2D vector (x, y)
        Vector2(float x, float y) : x(x), y(y) {}
        Vector2(int x, int y) : x(static_cast<float>(x)), y(static_cast<float>(y)) {}

		// Get the distance from the origin
        float Distance() const {
            return std::sqrt(x * x + y * y);
        }

		// Rotate the vector by angle (in radians)
        void Rotate(float angle) {
            float tx = x * std::cos(angle) - y * std::sin(angle);
            float ty = x * std::sin(angle) + y * std::cos(angle);
            x = tx;
            y = ty;
        }

		// Swap the x and y components
        void Swap() {
            std::swap(x, y);
        }

		// Operator overloads
        bool operator==(const Vector2& v) const { return x == v.x && y == v.y; }
        bool operator!=(const Vector2& v) const { return !(*this == v); }

        Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
        Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
        Vector2& operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
        Vector2& operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }
    };

}