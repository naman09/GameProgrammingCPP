#include "Component.h"

Component::Component(Actor* owner, int updateOrder) 
	: mOwner(owner), mUpdateOrder(updateOrder) {
	
	mOwner->AddComponent(this);
}

Component::~Component() {
	mOwner->RemoveComponent(this);
}

void Component::Update(const float& deltaTime) {
	
}
