#pragma once

#include "entity.h"
class Component
{
	Entity* owner;

public:
	virtual void		Update() = 0;
	Entity*				getOwner() { return owner; }
	void				setOwner(Entity* o) { owner = o; }
	virtual void		receiveMessage(Message *msg) = 0;
	~Component()		{ delete(owner); }
};