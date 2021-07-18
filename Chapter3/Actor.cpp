#include "Actor.h"
#include <cmath>

Actor::Actor(Game* game) 
	: mGame(game), mPosition(10.0f, 10.0f), mRotation(0.0f),
	mScale(1.0f) {
	game->AddActor(this); //type of "this" will be Actor but it will be pointing the same object only
	//that means if you call a function on this object it will case the derived version
}

Actor::~Actor() {
	mGame->RemoveActor(this);
	while (!mComponents.empty()) {
		delete mComponents.back();
	}
}

Vector2 Actor::GetForward() {
	return Vector2(cos(mRotation), -sin(mRotation));
}

void Actor::Update(const float& deltaTime) {}

void Actor::UpdateActor(const float& deltaTime) {}

void Actor::UpdateComponents(const float& deltaTime) {
}



//Inserting in ascending order of update order
void Actor::AddComponent(Component* component) {
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); iter++) {
		if ((*iter)->GetUpdateOrder() > component->GetUpdateOrder()) {
			break;
		}
	}
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component) {
	//TODO
}
