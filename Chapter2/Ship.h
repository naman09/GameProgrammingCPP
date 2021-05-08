#ifndef SHIP_H
#define SHIP_H

#include "Actor.h"
class Ship : public Actor {
	float mRightSpeed;
	float mDownSpeed;
public:
	Ship(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	float GetRightSpeed() const { return mRightSpeed; }
	float GetDownSpeed() const { return mDownSpeed; }
};

#endif
