#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include "Vector2.h"
#include "Component.h"

//Game object model
//Hybrid model = monolithic model + component-based model
class Actor {
public:
	enum class State {
		EActive, //update the actor
		EPaused,
		EDead //remove the actor
	};
	Actor(class Game* game); //dependency injection
	virtual ~Actor();
	
	void Update(float deltaTime); //updates components then actor
	void UpdateComponents(float deltaTime); //update components in order
	virtual void UpdateActor(float deltaTime); 
	void AddComponent(class Component* component); //sorts the components vector based on update order
	void RemoveComponent(class Component* component);
	
	Game* GetGame() const { return mGame; }
	State GetState() const { return mState; }
	void SetState(const State& state) { mState = state; }
	Vector2 GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& position) { mPosition = position; }
	float GetScale() const { return mScale; }
	void SetScale(const float& scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(const float& rotation) { mRotation = rotation; }
private:
	State mState;
	Vector2 mPosition;
	float mScale;
	float mRotation; //rotation in radians
	std::vector<class Component*> mComponents;

	//object will be injected used to create another actor 
	//or access any other Game functions
	class Game* mGame; 
};

#endif