#pragma once
#include "entity.h"

class Station :public Entity {
private:
	//Sprite* spritePtr;
public:
	Station() { this->setType(ENTITY_STATION); }
	void update();
};