#include "stdafx.h"
#include "entity_asteroid.h"
#include "game.h"
#include "globals.h"
#include "component.h"

void Asteroid::update() {
	std::vector<Component*> m_Components = this->getComponents();	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt) {
		(*compIt)->Update();
	}

}

void Asteroid::onCollision(vec2 pos, Entity *otherEntity) {

	//WE NEED TO SEND A MESSAGE TO THE COMPONENT_MOVABLE!!!
	//OutputDebugStringA("Asteroid Collision!\n");
	ComponentMovable *compMove = FindComponent<ComponentMovable>();
	if (compMove)
	{
		/*if (compMove->getVel().x > 0.0)
			compMove->setVel(vmake(compMove->getVel().x * -1.0, compMove->getVel().y));
		if (compMove->getVel().y < 0.0)
			compMove->setVel(vmake(compMove->getVel().x, compMove->getVel().y * -1.0));*/
		
		compMove->setVel(vmake(compMove->getVel().x * -1.0, compMove->getVel().y * -1.0));
		/*if (collidingAsteroid->getVel().x < 0.0) {
			collidingAsteroid->setVel(vmake(collidingAsteroid->getVel().x * -1.0, collidingAsteroid->getVel().y));
		}
		if (collidingAsteroid->getVel().y > 0.0) {
			collidingAsteroid->setVel(vmake(collidingAsteroid->getVel().x, collidingAsteroid->getVel().y * -1.0));
		}*/

	}
	/*if (this->getVel().x > 0.0)
		this->setVel(vmake(this->getVel().x * -1.0, this->getVel().y));
	if (this->getVel().y < 0.0)
		this->setVel(vmake(this->getVel().x, this->getVel().y * -1.0));


	if (otherEntity->getVel().x < 0.0) {
		otherEntity->setVel(vmake(collidingAsteroid->getVel().x * -1.0, collidingAsteroid->getVel().y));
	}
	if (otherEntity->getVel().y > 0.0) {
		otherEntity->setVel(vmake(collidingAsteroid->getVel().x, collidingAsteroid->getVel().y * -1.0));
	}*/
}


template<class T>
T* Asteroid::FindComponent()
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

bool Asteroid::isCollisionable() {
	ComponentCollisionable *comp = FindComponent<ComponentCollisionable>();
	if (comp)
		return true;
	else
		return false;
}
//void Asteroid::update() {
//
//	vec2 oldpos = this->getPos();
//	vec2 newpos = vadd(oldpos, this->getVel());
//
//	bool collision = false;
//	Asteroid* collidingAsteroid = nullptr;
//
//	//////////COLLISION WITH OTHER ASTEROIDS////////////
//	std::vector<Entity*> entities = game->getEntities();
//	for (auto entityIt = entities.begin(); entityIt != entities.end(); ++entityIt) {
//		if ((*entityIt)->getType() == ENTITY_ASTEROID) {
//			if (*entityIt != this)
//			{
//				float limit2 = (this->getRadius() + (*entityIt)->getRadius()) * (this->getRadius() + (*entityIt)->getRadius());
//				if (vlen2(vsub(newpos, (*entityIt)->getPos())) <= limit2)
//				{
//					collision = true;
//					collidingAsteroid = static_cast<Asteroid*>(*entityIt);
//					break;
//				}
//			}
//		}else if ((*entityIt)->getType() == ENTITY_PLAYER) {
//			float limitWithPlayer = (this->getRadius() + (*entityIt)->getRadius()) * (this->getRadius() + (*entityIt)->getRadius());
//			if (vlen2(vsub(this->getPos(), (*entityIt)->getPos())) <= limitWithPlayer){
//					
//					game->setPlayerCollision(true);
//					OutputDebugStringA("DEAD!!");
//					OutputDebugStringA("\n");
//					//player.setGfx(texExplosion);
//					//FONT_DrawString(vmake(SCR_WIDTH / 2 - 6 * 16, 16), "GAME OVER!");
//			}			
//		}
//	}
//
//	if (!collision) {
//		this->setPos(newpos);
//		this->getSprite()->setpos(newpos);
//	}
//	else
//	{
//		// Rebound!
//
//		if (this->getVel().x > 0.0)
//			this->setVel(vmake(this->getVel().x * -1.0, this->getVel().y));
//		if (this->getVel().y < 0.0)
//			this->setVel(vmake(this->getVel().x, this->getVel().y * -1.0));
//
//
//		if (collidingAsteroid->getVel().x < 0.0) {
//			collidingAsteroid->setVel(vmake(collidingAsteroid->getVel().x * -1.0, collidingAsteroid->getVel().y));
//		}
//		if (collidingAsteroid->getVel().y > 0.0) {
//			collidingAsteroid->setVel(vmake(collidingAsteroid->getVel().x, collidingAsteroid->getVel().y * -1.0));
//		}
//
//	}
//
//
//	// Rebound on margins
//	if (this->getVel().x > 0.0)
//	{
//		if (this->getPos().x + this->getRadius() > SCR_WIDTH)
//			this->setVel(vmake(this->getVel().x * -1.0, this->getVel().y));
//	}
//	else {
//		if (this->getPos().x - this->getRadius()< 0)
//			this->setVel(vmake(this->getVel().x * -1.0, this->getVel().y));
//	}
//	if (this->getVel().y > 0.0)
//	{
//		if (this->getPos().y + this->getRadius()> SCR_HEIGHT)
//			this->setVel(vmake(this->getVel().x, this->getVel().y * -1.0));
//	}
//	else {
//		if (this->getPos().y - this->getRadius()< 0)
//			this->setVel(vmake(this->getVel().x, this->getVel().y * -1.0));
//	}
//
//
//}