#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
protected: //making it inheritable
	class Actor* mOwner;

	//update order allows certain components to update before or after other components
	int mUpdateOrder; 
};

#endif