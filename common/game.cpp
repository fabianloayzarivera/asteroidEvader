#include "stdafx.h"
#include "game.h"
#include "application_manager.h"
#include "globals.h"

bool collideCircles(vec2 posA, float radiusA, vec2 posB, float radiusB) {
	float dist2 = (radiusA + radiusB) * (radiusA + radiusB);
	if (vlen2(vsub(posB, posA)) <= dist2)
		return true;
	else
		return false;
}

Game::Game() {

	// Load textures

	texAsteroid = CORE_LoadPNG("../data/asteroid.png", false);
	texSpaceBkg = CORE_LoadPNG("../data/space_bkg2.png", false);
	texStation = CORE_LoadPNG("../data/deathStar.png", false);
	texPlayer = CORE_LoadPNG("../data/space_ship.png", false);
	texExplosion = CORE_LoadPNG("../data/explosion.png", false);

	bkgHeight = 256;
	bkgWidth = 256;

	playerHeight = 45;
	playerWidth = 45;
	playerCollision = false;
	playerWin = false;

	stationWidth = 125;
	stationHeight = 125;

	Player* player = new Player();
	Station* station = new Station();

	player->setVel(vmake(PLAYER_MOVEMENT_SPEED_DEFAULT, PLAYER_MOVEMENT_SPEED_DEFAULT));
	player->setPos( vmake(SCR_WIDTH - playerWidth, playerHeight));
	player->setRadius( playerHeight > playerWidth ? playerHeight / 2 : playerWidth / 2);
	player->setGfx(texPlayer);
	player->setAngle(0);

	station->setPos( vmake(stationWidth / 2, SCR_HEIGHT - stationHeight / 2));
	station->setRadius( stationHeight > stationWidth ? stationHeight / 2 : stationWidth / 2);
	station->setGfx(texStation);
	station->setAngle(0);

	entities.push_back(player);
	entities.push_back(station);

	playerPtr = player; //THIS IS FOR THE INPUT MANAGER

	for (int i = 0; i < NUM_ASTEROIDS_DEFAULT; i++)
	{
		Asteroid* asteroid = new Asteroid();
		asteroid->setRadius(CORE_FRand(14.f, 100.f));
		asteroid->setPos(vmake(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));
		for (auto entityIt = entities.begin(); entityIt != entities.end(); ++entityIt) {
			if ((*entityIt)->getType() == ENTITY_ASTEROID) {
				while (collideCircles(asteroid->getPos(), asteroid->getRadius(), (*entityIt)->getPos(), (*entityIt)->getRadius())) {
					asteroid->setPos(vmake(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));
				}
			}
		}
		
		asteroid->setVel(vmake(CORE_FRand(-MAX_ASTEROID_SPEED, +MAX_ASTEROID_SPEED), CORE_FRand(-MAX_ASTEROID_SPEED, +MAX_ASTEROID_SPEED)));
		asteroid->setGfx(texAsteroid);
		asteroid->setAngle(0);
		entities.push_back(asteroid);
	}
}

Game::~Game() {
	CORE_UnloadPNG(texSpaceBkg);
	CORE_UnloadPNG(texAsteroid);
	CORE_UnloadPNG(texExplosion);
	CORE_UnloadPNG(texStation);
	CORE_UnloadPNG(texPlayer);
}

void Game::render() {
	
	// Render
	glClear(GL_COLOR_BUFFER_BIT);

	// Render backgground
	for (int i = 0; i <= SCR_WIDTH / bkgWidth; i++)
		for (int j = 0; j <= SCR_HEIGHT / bkgHeight; j++)
			CORE_RenderCenteredSprite(vmake(i * bkgWidth, j * bkgHeight), vmake(bkgHeight, bkgWidth), texSpaceBkg);



	for (auto entityIt = entities.begin(); entityIt != entities.end(); ++entityIt) {
		if ((*entityIt)->getType() == ENTITY_ASTEROID) {
			CORE_RenderCenteredSprite((*entityIt)->getPos(), vmake((*entityIt)->getRadius() * 2.f, (*entityIt)->getRadius() * 2.f), (*entityIt)->getGfx());
		}else if((*entityIt)->getType() == ENTITY_STATION) {
			CORE_RenderCenteredSprite((*entityIt)->getPos(), vmake(stationWidth, stationHeight), (*entityIt)->getGfx());
		}else if ((*entityIt)->getType() == ENTITY_PLAYER) {
			CORE_RenderCenteredRotatedSprite((*entityIt)->getPos(), vmake(playerWidth, playerHeight), (*entityIt)->getAngle(), (*entityIt)->getGfx());
		}
	}
	


	SYS_Show();
}

void Game::run() {

	for (auto entityIt = entities.begin(); entityIt != entities.end(); ++entityIt) {
		(*entityIt)->update();
	}
	checkPlayerCollision();

}

void Game::checkPlayerCollision() {

	if (playerCollision) {
		appManager->switchMode(MODE_GAMEOVER);
	}

}

void Game::runAsteroids() {
	
}
//void Game::processInput() {
//	//// Move Player
//	//if (SYS_KeyPressed(SYS_KEY_UP)) {
//	//	movePlayer();
//	//}
//	//// Rotate Player
//	//if (SYS_KeyPressed(SYS_KEY_LEFT)) {
//	//	rotatePlayerLeft();
//	//}
//
//	//if (SYS_KeyPressed(SYS_KEY_RIGHT)) {
//	//	rotatePlayerRight();
//	//}
//
//}

void Game::movePlayer() {
	vec2 oldPosPlayer = playerPtr->getPos();
	float trueAngle = playerPtr->getAngle() + M_PIf / 2;
	float angleFactorX = cos(trueAngle);
	float angleFactorY = sin(trueAngle);
	vec2 vectorMove = vmake(playerPtr->getVel().x * angleFactorX, playerPtr->getVel().y * angleFactorY);
	vec2 newPosPlayer = vadd(oldPosPlayer, vectorMove);
	playerPtr->setPos( newPosPlayer);

	/*if (collideCircles(playerPtr->getPos(), playerPtr->getRadius(), stationPtr->getPos(), stationPtr->getRadius())) {
		playerWin = true;
	}*/   //move to player collision Function
}

void Game::rotatePlayerLeft() {
	playerPtr->setAngle(playerPtr->getAngle() + PLAYER_ROTATION_SPEED_DEFAULT);
	if (playerPtr->getAngle() >= 2 * M_PIf)
		playerPtr->setAngle( 0);

}

void Game::rotatePlayerRight() {
	playerPtr->setAngle(playerPtr->getAngle() - PLAYER_ROTATION_SPEED_DEFAULT);
	if (playerPtr->getAngle() <= 0)
		playerPtr->setAngle(2 * M_PIf);

}