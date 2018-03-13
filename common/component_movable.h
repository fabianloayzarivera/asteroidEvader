#pragma once
#include "component.h"

class ComponentMovable : public Component {
private:
	vec2 vel;
public:
	const vec2 getVel() { return vel; }
	void setVel(const vec2 v) { vel = v; }
	void Update();
	void receiveMessage(Message *msg) {}
};