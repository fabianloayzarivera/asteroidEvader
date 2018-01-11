#include "stdafx.h"
#include "graphics_engine.h"

void GraphicsEngine::render() {
	glClear(GL_COLOR_BUFFER_BIT);
	Sprite* sprite;
	vector<Entity*> entities = game->getEntities();
	// Render backgground
	for (int i = 0; i <= SCR_WIDTH / bkgWidth; i++)
		for (int j = 0; j <= SCR_HEIGHT / bkgHeight; j++)
			CORE_RenderCenteredSprite(vmake(i * bkgWidth, j * bkgHeight), vmake(bkgHeight, bkgWidth), texBkg);



	for (auto entityIt = entities.begin(); entityIt != entities.end(); ++entityIt) {
		sprite = (*entityIt)->getSprite();
		if (sprite) {
			if ((*entityIt)->getType() == ENTITY_ASTEROID) {
				CORE_RenderCenteredSprite(sprite->getPos(), vmake((*entityIt)->getRadius() * 2.f, (*entityIt)->getRadius() * 2.f), sprite->getGfx());
			}
			else if ((*entityIt)->getType() == ENTITY_STATION) {
				CORE_RenderCenteredSprite(sprite->getPos(), vmake(sprite->getWidth(), sprite->getHeight()), sprite->getGfx());
			}
			else if ((*entityIt)->getType() == ENTITY_PLAYER) {
				CORE_RenderCenteredRotatedSprite(sprite->getPos(), vmake(sprite->getWidth(), sprite->getHeight()), sprite->getAngle(), sprite->getGfx());
			}
		}
	}


}