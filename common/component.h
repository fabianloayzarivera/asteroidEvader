#pragma once
#include "entity.h"

class Component
{
	Entity* owner;
public:
	virtual void Update() = 0;
	Entity* getOwner() { return owner; }
};