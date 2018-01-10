#include "stdafx.h"
#include "entity_asteroid.h"
#include "game.h"
#include "globals.h"

void Asteroid::update() {

	vec2 oldpos = this->getPos();
	vec2 newpos = vadd(oldpos, this->getVel());

	bool collision = false;
	Asteroid* collidingAsteroid = nullptr;

	//////////COLLISION WITH OTHER ASTEROIDS////////////
	std::vector<Entity*> entities = game->getEntities();
	for (auto entityIt = entities.begin(); entityIt != entities.end(); ++entityIt) {
		if ((*entityIt)->getType() == ENTITY_ASTEROID) {
			if (*entityIt != this)
			{
				float limit2 = (this->getRadius() + (*entityIt)->getRadius()) * (this->getRadius() + (*entityIt)->getRadius());
				if (vlen2(vsub(newpos, (*entityIt)->getPos())) <= limit2)
				{
					collision = true;
					collidingAsteroid = static_cast<Asteroid*>(*entityIt);
					break;
				}
			}
		}else if ((*entityIt)->getType() == ENTITY_PLAYER) {
			float limitWithPlayer = (this->getRadius() + (*entityIt)->getRadius()) * (this->getRadius() + (*entityIt)->getRadius());
			if (vlen2(vsub(this->getPos(), (*entityIt)->getPos())) <= limitWithPlayer){
					
					game->setPlayerCollision(true);
					OutputDebugStringA("DEAD!!");
					OutputDebugStringA("\n");
					//player.setGfx(texExplosion);
					//FONT_DrawString(vmake(SCR_WIDTH / 2 - 6 * 16, 16), "GAME OVER!");
			}			
		}
	}

	if (!collision)
		this->setPos(newpos);
	else
	{
		// Rebound!

		if (this->getVel().x > 0.0)
			this->setVel(vmake(this->getVel().x * -1.0, this->getVel().y));
		if (this->getVel().y < 0.0)
			this->setVel(vmake(this->getVel().x, this->getVel().y * -1.0));


		if (collidingAsteroid->getVel().x < 0.0) {
			collidingAsteroid->setVel(vmake(collidingAsteroid->getVel().x * -1.0, collidingAsteroid->getVel().y));
		}
		if (collidingAsteroid->getVel().y > 0.0) {
			collidingAsteroid->setVel(vmake(collidingAsteroid->getVel().x, collidingAsteroid->getVel().y * -1.0));
		}

	}


	// Rebound on margins
	if (this->getVel().x > 0.0)
	{
		if (this->getPos().x + this->getRadius() > SCR_WIDTH)
			this->setVel(vmake(this->getVel().x * -1.0, this->getVel().y));
	}
	else {
		if (this->getPos().x - this->getRadius()< 0)
			this->setVel(vmake(this->getVel().x * -1.0, this->getVel().y));
	}
	if (this->getVel().y > 0.0)
	{
		if (this->getPos().y + this->getRadius()> SCR_HEIGHT)
			this->setVel(vmake(this->getVel().x, this->getVel().y * -1.0));
	}
	else {
		if (this->getPos().y - this->getRadius()< 0)
			this->setVel(vmake(this->getVel().x, this->getVel().y * -1.0));
	}


}