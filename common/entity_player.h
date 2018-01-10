#pragma once
#include "entity.h"
#include "sprite.h"

class Player :public Entity{
private:
	//Sprite* spritePtr;
	vec2   vel;
	float  angle;

public:
	Player() { vel = vmake(0, 0); angle = 0;  this->setType(ENTITY_PLAYER); }
	const vec2 getVel() { return vel; }
	void setVel(const vec2 v) { vel = v; }
	void update() {}
};