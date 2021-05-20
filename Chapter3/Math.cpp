#include "Math.h"

Vector2 Vector2::Zero(0.0f, 0.0f);

bool Math::NearZero(const float& value) {
	if (abs(value) <= epsilon) return true;
	return false;
}