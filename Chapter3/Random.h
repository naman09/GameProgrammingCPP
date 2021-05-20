#ifndef RANDOM_H
#define RANDOM_H

#include "Math.h"
#include <cstdlib>

class Random {
public:
	//Assuming that rand()%0 is not happening
	static Vector2 GetVector(const Vector2& startVec2, const Vector2& endVec2);
};

#endif

