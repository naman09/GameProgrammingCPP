#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2 {
	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float a, float b) : x(a), y(b) {}
	float x;
	float y;
};

#endif // !VECTOR2_H

