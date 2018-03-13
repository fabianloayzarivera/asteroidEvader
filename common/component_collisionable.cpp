	#include "stdafx.h"
	#include "component_collisionable.h"
	#include "game.h"
	#include "globals.h"

	void ComponentCollisionable::Update() {
		bool collision = false;
		vec2 pos;
		Entity *collidingEntity = nullptr;
		//////////COLLISION WITH OTHER ASTEROIDS////////////
		std::vector<Entity*> entities = game->getEntities();
		for (auto entityIt = entities.begin(); entityIt != entities.end(); ++entityIt) {
			//if ((*entityIt)->getType() == ENTITY_ASTEROID) {
				if (*entityIt != this->getOwner())
				{
					float limit2 = (this->getOwner()->getRadius() + (*entityIt)->getRadius()) * (this->getOwner()->getRadius() + (*entityIt)->getRadius());
					if (vlen2(vsub(this->getOwner()->getPos(), (*entityIt)->getPos())) <= limit2)
					{
						collision = true;
						collidingEntity = (*entityIt);
						pos = this->getOwner()->getPos();
						break;
					}
				}	
			//}
		}
	
		if (!collision) {
			//SEND MESSAGE
			CollisionMessage msg;
			msg.posCollision = pos;
			msg.otherEntity = collidingEntity;
			game->sendMessage(&msg);

		}

	}

	void ComponentCollisionable::receiveMessage(Message *msg) {
		
		CollisionMessage *colMsg = dynamic_cast<CollisionMessage*>(msg);
		if (colMsg) {
		
			this->getOwner()->onCollision(colMsg->posCollision, colMsg->otherEntity);
		
		}
	
	}