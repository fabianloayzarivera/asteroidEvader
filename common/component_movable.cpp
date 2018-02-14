#include "stdafx.h"
#include "component_movable.h"

void ComponentMovable::move() {
	vec2 oldPos = this->getPos();
	float trueAngle = this->getAngle() + M_PIf / 2;
	float angleFactorX = cos(trueAngle);
	float angleFactorY = sin(trueAngle);
	vec2 vectorMove = vmake(this->getVel().x * angleFactorX, this->getVel().y * angleFactorY);
	vec2 newPos = vadd(oldPos, vectorMove);
	this->setPos(newPos);
	getOwner()->getSprite()->setpos(newPos);

}

void ComponentMovable::rotateLeft() {
	this->setAngle(this->getAngle() + PLAYER_ROTATION_SPEED_DEFAULT);
	if (this->getAngle() >= 2 * M_PIf)
		this->setAngle(0);
	getOwner()->getSprite()->setAngle(this->getAngle());

}

void ComponentMovable::rotateRight() {
	this->setAngle(this->getAngle() - PLAYER_ROTATION_SPEED_DEFAULT);
	if (this->getAngle() <= 0)
		this->setAngle(2 * M_PIf);
	getOwner()->getSprite()->setAngle(this->getAngle());

}

