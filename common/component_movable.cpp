#include "stdafx.h"
#include "component_movable.h"
#include "game.h"
#include "globals.h"

void ComponentMovable::Update() {
	vec2 oldpos = this->getOwner()->getPos();
	vec2 newpos = vadd(oldpos, this->getVel());
	this->getOwner()->setPos(newpos);
	this->getOwner()->getSprite()->setpos(newpos);


	if (this->getVel().x > 0.0)
	{
		if (this->getOwner()->getPos().x + this->getOwner()->getRadius() > SCR_WIDTH)
			this->setVel(vmake(this->getVel().x * -1.0, this->getVel().y));
	}
	else {
		if (this->getOwner()->getPos().x - this->getOwner()->getRadius()< 0)
			this->setVel(vmake(this->getVel().x * -1.0, this->getVel().y));
	}
	if (this->getVel().y > 0.0)
	{
		if (this->getOwner()->getPos().y + this->getOwner()->getRadius()> SCR_HEIGHT)
			this->setVel(vmake(this->getVel().x, this->getVel().y * -1.0));
	}
	else {
		if (this->getOwner()->getPos().y - this->getOwner()->getRadius()< 0)
			this->setVel(vmake(this->getVel().x, this->getVel().y * -1.0));
	}
}