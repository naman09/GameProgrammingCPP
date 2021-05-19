#include "Math.h"

bool Math::NearZero(const float& value) {
	if (abs(value) <= epsilon) return true;
	return false;
}