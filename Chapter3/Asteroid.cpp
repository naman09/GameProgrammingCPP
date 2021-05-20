#include "Asteroid.h"
#include "MoveComponent.h"
#include "Random.h"

Asteroid::Asteroid(Game* game) : Actor(game) {
	Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
	SetPosition(randPos);
	MoveComponent* move = new MoveComponent(this);
	move->SetForwardSpeed(150.0f);
}
