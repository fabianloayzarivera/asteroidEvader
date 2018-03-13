#pragma once
#include "entity.h"

class Asteroid :public Entity{
private:

	vec2   vel;
public:
	Asteroid() { vel = vmake(0,0); this->setType(ENTITY_ASTEROID); }
	void update();
	void onCollision(vec2 pos, Entity *otherEntity);
	template<class T> T*    FindComponent();
};