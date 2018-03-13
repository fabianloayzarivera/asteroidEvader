#pragma once
#include "component.h"

class ComponentCollisionable : public Component {
private:
	
public:
	void Update();
	void receiveMessage(Message *msg);
};