#pragma once
#include <cmath>

namespace AxionForge {

	class Vector2 {
	public:
		float x = 0;
		float y = 0;

		// Create a 2D vector (0, 0)
		Vector2() { x = 0; y = 0; }
		// Create a 2D vector (x, y)
		Vector2(float x, float y) {
			this->x = x;
			this->y = y;
		}
		Vector2(int x, int y) : Vector2((float)x, (float)y) {}
		// Create a 2D vector (x, x)
		Vector2(float x) : Vector2(x, x) {}
		Vector2(int x) : Vector2((float)x, (float)x) {}

		// Get the distance from the origin
		float Distance() const {
			return std::sqrt(x * x + y * y);
		}

		// Operator overloads
		bool operator==(const Vector2& v) const { return x == v.x && y == v.y; }
		bool operator!=(const Vector2& v) const { return !(*this == v); }
		bool operator<(const Vector2& v) const { return x < v.x && y < v.y; }
		bool operator>(const Vector2& v) const { return x > v.x && y > v.y; }
		bool operator<=(const Vector2& v) const { return x <= v.x && y <= v.y; }
		bool operator>=(const Vector2& v) const { return x >= v.x && y >= v.y; }

		Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
		Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
		Vector2& operator+=(const Vector2& v) { return *this = *this + v; }
		Vector2& operator-=(const Vector2& v) { return *this = *this - v; }
	};

}