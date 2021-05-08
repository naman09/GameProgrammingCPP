#include "Actor.h"

Actor::Actor(Game* game) : mGame(game) {
	mPosition.x = 10.0f;
	mPosition.y = 10.0f;
	mRotation = 0;
	mScale = 1;
	mState = State::EActive;
}

Actor::~Actor() {}

void Actor::Update(float deltaTime) {
}

void Actor::UpdateComponents(float deltaTime) {
}

void Actor::UpdateActor(float deltaTime) {
}

void Actor::AddComponent(Component* component) {
}

void Actor::RemoveComponent(Component* component) {
}

