#pragma once
#include "entity.h"

class Station :public Entity {
private:
	//Sprite* spritePtr;
public:
	Station() { this->setType(ENTITY_STATION); }
	void update();
	bool isCollisionable();
	template<class T> T*    FindComponent();
	void onCollision(vec2 pos, Entity *otherEntity) {}
};