#pragma once
#include "entity.h"

class Asteroid :public Entity{
private:
	//Sprite* spritePtr;
	vec2   vel;
public:
	Asteroid() { vel = vmake(0,0); this->setType(ENTITY_ASTEROID); }
	const vec2 getVel() { return vel; }
	void setVel(const vec2 v) { vel = v; }
	void update();
};