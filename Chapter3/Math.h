#ifndef MATH_H
#define MATH_H

#include <cmath>

namespace Math {


};

class Vector2 {
public:
	float x;
	float y;
	Vector2() : x{ 0.0f }, y{ 0.0f } {}
	Vector2(const float& _x, const float& _y) : x{ _x }, y{ _y } {}
	//a+b
	Vector2 operator+(const Vector2& other) {
		return Vector2{ x + other.x,y + other.y };
	}
	//a-b
	Vector2 operator-(const Vector2& other) {
		return Vector2{ x - other.x,y - other.y };
	}
	//Vector2 * scalar
	Vector2 operator*(const float& scalar) { //member function is overloaded
		return Vector2{ x * scalar,y * scalar };
	}
	//scalar * Vector2
	friend Vector2 operator*(const float& scalar, const Vector2& vec2) {
		return Vector2{ scalar * vec2.x,scalar * vec2.y };
	}
	//Length
	float Length() const {
		return sqrt(x * x + y * y);
	}
	//SqauredLength
	float LengthSquared() const {
		return x * x + y * y;
	}
	//Normalize --> in place , return new vector2
	void Normalize() { //in place
		float len = Length();
		if (len == 0.0f) return;
		x /= len;
		y /= len;
	}
	static Vector2 Normalize(const Vector2& vec2) {
		Vector2 ans{ vec2 };
		ans.Normalize();
		return ans;
	}
};

#endif
