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
	for (auto& component : mComponents) {
		component->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime) {}

void Actor::AddComponent(Component* component) {
	int myUpdateOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); iter++) {
		if ((*iter)->GetUpdateOrder() > myUpdateOrder) {
			break;
		}
	}
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component) {
	while (!mComponents.size()) {
		delete mComponents.back();
		mComponents.pop_back();
	}
}

