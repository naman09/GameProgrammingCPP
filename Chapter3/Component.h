#ifndef COMPONENT_H
#define COMPONENT_H

#include "Actor.h"

class Component {
public:
	Component(class Actor* owner, int updateOrder = 10);
	virtual ~Component();
	virtual void Update(const float& deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	class Actor* mOwner;
	int mUpdateOrder;
};

#endif

