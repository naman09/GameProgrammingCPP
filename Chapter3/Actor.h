#ifndef ACTOR_H
#define ACTOR_H

#include "Game.h"
#include "Component.h"
#include <vector>
#include "Math.h"

class Actor {
	class Game* mGame;
	std::vector<class Component*> mComponents;
	Vector2 mPosition;
	float mScale;
	float mRotation;
public:
	Actor(class Game* game);
	virtual ~Actor();
	void Update(const float& deltaTime);
	void UpdateActor(const float& deltaTime);
	void UpdateComponents(const float& deltaTime);	
	void AddComponent(Component* component);
	Vector2 GetPosition() const { return mPosition; }
	float GetRotation() const { return mRotation; }
	void SetPosition(const Vector2& position) { mPosition = position; }
	void SetRotation(const float& rotation) { mRotation = rotation; }
	Vector2 GetForward(); //returns unit vector using mPos
};

#endif 

