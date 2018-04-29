#include "stdafx.h"
#include "entity_asteroid.h"
#include "game.h"
#include "globals.h"

void Player::update() {
	std::vector<Component*> m_Components = this->getComponents();	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt) {
		(*compIt)->Update();
	}

}

template<class T>
T* Player::FindComponent()
{
	std::vector<Component*> m_Components = this->getComponents();
	for (auto compIt = m_Components.begin();
		compIt != m_Components.end();
		++compIt)
	{
		T* comp = dynamic_cast<T*>(*compIt);
		if (comp)
			return comp;
	}
	return NULL;
}

void Player::onCollision(vec2 pos, Entity *otherEntity) {

	ComponentCollisionable *comp = FindComponent<ComponentCollisionable>();
	if (comp) {
		if (otherEntity->getType() == ENTITY_ASTEROID) {
			OutputDebugStringA("Player Dead! \n");
			game->setPlayerCollision(true);
		}
	}
		

}

bool Player::isCollisionable() {
	ComponentCollisionable *comp = FindComponent<ComponentCollisionable>();
	if (comp)
		return true;
	else
		return false;
}