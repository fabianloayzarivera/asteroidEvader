#pragma once
#include "component.h"

class ComponentPlayerController : public Component {
private:
	vec2   vel;
	//float  angle;
public:
	void Update() {}
	const vec2 getVel() { return vel; }
	void setVel(const vec2 v) { vel = v; }
	void movePlayer();
	void rotatePlayerLeft();
	void rotatePlayerRight();
	void receiveMessage(Message *msg);
};