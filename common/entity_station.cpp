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