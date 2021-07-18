#include "Actor.h"
#include "Game.h"

Actor::Actor(Game* game) 
	: mGame(game) , mPosition(10.0f, 10.0f), mRotation(0.0f), 
	mScale(1.0f), mState(State::EActive) {

	mGame->AddActor(this);
}

Actor::~Actor() {
	mGame->RemoveActor(this);
	while (!mComponents.empty()) {
		delete mComponents.back();
	}
}


void Actor::Update(float deltaTime) {
	if (mState == State::EActive) {
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
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
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end()) {
		mComponents.erase(iter);
	}
} 

