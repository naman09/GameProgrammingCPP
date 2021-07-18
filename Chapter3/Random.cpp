#include "Random.h"

//Assuming that rand()%0 is not happening
Vector2 Random::GetVector(const Vector2& startVec2, const Vector2& endVec2) {
	int tmpX = rand() % (static_cast<int>(std::fabs(endVec2.x - startVec2.x)));
	int tmpY = rand() % (static_cast<int>(std::fabs(endVec2.y - startVec2.y)));
	return Vector2(static_cast<float>(tmpX), static_cast<float>(tmpY));
}