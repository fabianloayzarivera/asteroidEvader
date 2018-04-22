#include "stdafx.h"
#include "entity_station.h"
#include "game.h"
#include "globals.h"

void Station::update() {

	vec2 stationPos = this->getPos();
	bool collision = false;
	Asteroid* collidingAsteroid = nullptr;

	//////////COLLISION WITH PLAYER////////////
	std::vector<Entity*> entities = game->getEntities();
	for (auto entityIt = entities.begin(); entityIt != entities.end(); ++entityIt) {
		
		if ((*entityIt)->getType() == ENTITY_PLAYER) {
			float limitWithPlayer = (this->getRadius() + (*entityIt)->getRadius()) * (this->getRadius() + (*entityIt)->getRadius());
			if (vlen2(vsub(this->getPos(), (*entityIt)->getPos())) <= limitWithPlayer) {

				game->setPlayerWin(true);
				OutputDebugStringA("WIN!!");
				OutputDebugStringA("\n");
				
			}
		}
	}	

}

template<class T>
T* Station::FindComponent()
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

bool Station::isCollisionable() {
	ComponentCollisionable *comp = FindComponent<ComponentCollisionable>();
	if (comp)
		return true;
	else
		return false;
}