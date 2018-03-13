#include "stdafx.h"
#include "entity_asteroid.h"
#include "game.h"
#include "globals.h"

//void Player::movePlayer() {
//	vec2 oldPosPlayer = this->getPos();
//	float trueAngle = this->getAngle() + M_PIf / 2;
//	float angleFactorX = cos(trueAngle);
//	float angleFactorY = sin(trueAngle);
//	vec2 vectorMove = vmake(this->getVel().x * angleFactorX, this->getVel().y * angleFactorY);
//	vec2 newPosPlayer = vadd(oldPosPlayer, vectorMove);
//	this->setPos(newPosPlayer);
//	this->getSprite()->setpos(newPosPlayer);
//
//
//
//}
//void Player::rotatePlayerLeft() {
//	this->setAngle(this->getAngle() + PLAYER_ROTATION_SPEED_DEFAULT);
//	if (this->getAngle() >= 2 * M_PIf)
//		this->setAngle(0);
//	this->getSprite()->setAngle(this->getAngle());
//
//}
//
//void Player::rotatePlayerRight() {
//	this->setAngle(this->getAngle() - PLAYER_ROTATION_SPEED_DEFAULT);
//	if (this->getAngle() <= 0)
//		this->setAngle(2 * M_PIf);
//	this->getSprite()->setAngle(this->getAngle());
//
//}

void Player::update() {
	std::vector<Component*> m_Components = this->getComponents();	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt) {
		(*compIt)->Update();
	}

}