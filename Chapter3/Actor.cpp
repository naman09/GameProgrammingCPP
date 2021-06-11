#include "Actor.h"
#include <cmath>

Actor::Actor(Game* game) {
	game->AddActor(this); //type of "this" will be Actor but it will be pointing the same object only
	//that means if you call a function on this object it will case the derived version
}

Vector2 Actor::GetForward() {
	return Vector2(cos(mRotation), -sin(mRotation));
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
