#include "stdafx.h"
#include "component_player_controller.h"
#include "game.h"
#include "globals.h"

void ComponentPlayerController::movePlayer() {
	vec2 oldPosPlayer = this->getOwner()->getPos();
	float trueAngle = this->getOwner()->getAngle() + M_PIf / 2;
	float angleFactorX = cos(trueAngle);
	float angleFactorY = sin(trueAngle);
	vec2 vectorMove = vmake(this->getVel().x * angleFactorX, this->getVel().y * angleFactorY);
	vec2 newPosPlayer = vadd(oldPosPlayer, vectorMove);
	this->getOwner()->setPos(newPosPlayer);
	this->getOwner()->getSprite()->setpos(newPosPlayer);



}
void ComponentPlayerController::rotatePlayerLeft() {
	this->getOwner()->setAngle(this->getOwner()->getAngle() + rotationSpeed);
	if (this->getOwner()->getAngle() >= 2 * M_PIf)
		this->getOwner()->setAngle(0);
	this->getOwner()->getSprite()->setAngle(this->getOwner()->getAngle());

}

void ComponentPlayerController::rotatePlayerRight() {
	this->getOwner()->setAngle(this->getOwner()->getAngle() - rotationSpeed);
	if (this->getOwner()->getAngle() <= 0)
		this->getOwner()->setAngle(2 * M_PIf);
	this->getOwner()->getSprite()->setAngle(this->getOwner()->getAngle());

}

void ComponentPlayerController::receiveMessage(Message *msg) {
	UpMessage *moveMsg = dynamic_cast<UpMessage*>(msg);
	if (moveMsg) {
		if (moveMsg->up) {
			this->movePlayer();
		}
	}

	RotateLeftMessage *rotLeftMsg = dynamic_cast<RotateLeftMessage*>(msg);
	if (rotLeftMsg) {
		if (rotLeftMsg->rotate) {
			this->rotatePlayerLeft();
		}
	}
	
	RotateRightMessage *rotRightMsg = dynamic_cast<RotateRightMessage*>(msg);
	if (rotRightMsg) {
		if (rotRightMsg->rotate) {
			this->rotatePlayerRight();
		}
	}

}