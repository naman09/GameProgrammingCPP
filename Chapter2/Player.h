#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "AnimSpriteComponent.h"
class Player : public Actor {
	float moveRight;
	float moveUp;
	AnimSpriteComponent* moveAnim;
	AnimSpriteComponent* jumpAnim;
public:
	Player(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
};

#endif
