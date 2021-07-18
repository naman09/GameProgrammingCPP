#ifndef MOVE_COMPONENT_H
#define MOVE_COMPONENT_H

#include "Component.h"
class MoveComponent : public Component {
public:
	MoveComponent(Actor* owner, int updateOrder = 10);
	void Update(const float& deltaTime) override;
	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetAngularSpeed(const float& angularSpeed) { mAngularSpeed = angularSpeed; }
	void SetForwardSpeed(const float& forwardSpeed) { mForwardSpeed = forwardSpeed; }
private:
	float mAngularSpeed;
	float mForwardSpeed;
};

#endif
