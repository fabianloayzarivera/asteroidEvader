#include "stdafx.h"
#include "game.h"
#include "application_manager.h"
#include "input_manager.h"
#include "graphics_engine.h"
#include "language_manager.h"
#include "globals.h"
#include <fstream>
#include <string>
#include "./rapidjson/document.h"
using namespace rapidjson;

bool collideCircles(vec2 posA, float radiusA, vec2 posB, float radiusB) {
	float dist2 = (radiusA + radiusB) * (radiusA + radiusB);
	if (vlen2(vsub(posB, posA)) <= dist2)
		return true;
	else
		return false;
}

Game::Game(int level) {
	//LOAD JSON FILE
	std::ifstream ifs("../data/gamedata.json");
	std::string content((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));

	Document document;
	document.Parse(content.c_str()); // its not returning the value parsed!!!
	OutputDebugStringA(content.c_str());
	if (document.IsObject()) 
	{
		//LOAD DEFAULT ATTRIBUTES
		bkgHeight = document["bkgHeight"].GetFloat();
		bkgWidth = document["bkgWidth"].GetFloat();
		playerHeight = document["playerHeight"].GetFloat();
		playerWidth = document["playerWidth"].GetFloat();
		stationWidth = document["stationWidth"].GetFloat();
		stationHeight = document["stationHeight"].GetFloat();
		//OutputDebugStringA(document["texAsteroid"].GetString());

		if (document.HasMember("levels"))
		{
			const Value& levels = document["levels"];
			if (levels.IsArray()) {
				int levelsSize = levels.Size();
				appManager->setLevelAmount(levelsSize);
				/*std::string s = std::to_string(levelsSize);
				char const *pchar = s.c_str();
				OutputDebugStringA(pchar);*/
				if (level < levelsSize) 
				{ 
					//GET CURRENT LEVEL
					const Value& levelSelected = levels[level];
					if (levelSelected.IsObject())
					{
						OutputDebugStringA(levelSelected["name"].GetString());

						texAsteroid = CORE_LoadPNG(levelSelected["texAsteroid"].GetString(), false);
						texSpaceBkg = CORE_LoadPNG(levelSelected["texSpaceBkg"].GetString(), false);
						texStation = CORE_LoadPNG(levelSelected["texStation"].GetString(), false);
						texPlayer = CORE_LoadPNG(levelSelected["texPlayer"].GetString(), false);
						texExplosion = CORE_LoadPNG(levelSelected["texExplosion"].GetString(), false);

						player_movement_speed = levelSelected["player_movement_speed"].GetFloat();
						player_rotation_speed = levelSelected["player_rotation_speed"].GetFloat();
						asteroid_num = levelSelected["asteroid_num"].GetInt();
						asteroid_max_speed = levelSelected["asteroid_max_speed"].GetFloat();
					}
				}
				else 
				{
					OutputDebugStringA("No more Levels!");
				}
				
				
			}
			
		}
			
	}
	//LOAD LANGUAGE
	//OutputDebugStringA(document["texAsteroid"].GetString());


	// Load textures

	/*texAsteroid = CORE_LoadPNG("../data/asteroid.png", false);
	texSpaceBkg = CORE_LoadPNG("../data/space_bkg2.png", false);
	texStation = CORE_LoadPNG("../data/deathStar.png", false);
	texPlayer = CORE_LoadPNG("../data/space_ship.png", false);
	texExplosion = CORE_LoadPNG("../data/explosion.png", false);*/

	/*bkgHeight = 256;
	bkgWidth = 256;*/

	graphicsEngine->setBkgWidth(bkgWidth);
	graphicsEngine->setBkgHeight(bkgHeight);
	graphicsEngine->setTexBkg(texSpaceBkg);

	//playerHeight = 45;
	//playerWidth = 45;
	playerCollision = false;
	playerWin = false;

	//stationWidth = 125;
	//stationHeight = 125;

	Player* player = new Player();
	Station* station = new Station();

	//player->setVel(vmake(PLAYER_MOVEMENT_SPEED_DEFAULT, PLAYER_MOVEMENT_SPEED_DEFAULT));
	//player->setVel(vmake(player_movement_speed, player_movement_speed));
	player->setPos( vmake(SCR_WIDTH - playerWidth, playerHeight));
	player->setRadius( playerHeight > playerWidth ? playerHeight / 2 : playerWidth / 2);
	player->setGfx(texPlayer);
	player->setAngle(0);
	player->setType(ENTITY_PLAYER);

	Sprite* playerSprite = new Sprite(player->getPos(), playerWidth, playerHeight, player->getAngle(), texPlayer);
	player->setSprite(playerSprite);
	graphicsEngine->pushSprite(playerSprite);


	station->setPos( vmake(stationWidth / 2, SCR_HEIGHT - stationHeight / 2));
	station->setRadius( stationHeight > stationWidth ? stationHeight / 2 : stationWidth / 2);
	station->setGfx(texStation);
	station->setAngle(0);

	Sprite* stationSprite = new Sprite(station->getPos(), stationWidth, stationHeight, station->getAngle(), texStation);
	station->setSprite(stationSprite);
	graphicsEngine->pushSprite(stationSprite);
	
	//ComponentMovable *c_Movable = new ComponentMovable();
	//c_Movable->setOwner(player);
	//c_Movable->setVel(vmake(CORE_FRand(-MAX_ASTEROID_SPEED, +MAX_ASTEROID_SPEED), CORE_FRand(-MAX_ASTEROID_SPEED, +MAX_ASTEROID_SPEED)));
	//player->addComponent(c_Movable);

	ComponentPlayerController *c_PlayerController = new ComponentPlayerController();
	c_PlayerController->setOwner(player);
	c_PlayerController->setVel(vmake(player_movement_speed, player_movement_speed));
	c_PlayerController->setRotSpeed(player_rotation_speed);
	player->addComponent(c_PlayerController);

	ComponentCollisionable *c_PlayerCollision = new ComponentCollisionable();
	c_PlayerCollision->setOwner(player);
	player->addComponent(c_PlayerCollision);

	entities.push_back(player);
	entities.push_back(station);

	//inputManager->setPlayerPtr(player); //THIS IS FOR THE INPUT MANAGER

	for (int i = 0; i < asteroid_num; i++)
	{
		Asteroid* asteroid = new Asteroid();
		asteroid->setRadius(CORE_FRand(14.f, 100.f));
		asteroid->setPos(vmake(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));
		for (auto entityIt = entities.begin(); entityIt != entities.end(); ++entityIt) {
			if (((*entityIt)->getType() == ENTITY_ASTEROID)||((*entityIt)->getType() == ENTITY_PLAYER)){
				while (collideCircles(asteroid->getPos(), asteroid->getRadius(), (*entityIt)->getPos(), (*entityIt)->getRadius())) {
					asteroid->setPos(vmake(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));
				}
			}
		}
		
		//asteroid->setVel(vmake(CORE_FRand(-MAX_ASTEROID_SPEED, +MAX_ASTEROID_SPEED), CORE_FRand(-MAX_ASTEROID_SPEED, +MAX_ASTEROID_SPEED)));
		asteroid->setGfx(texAsteroid);
		asteroid->setAngle(0);
		asteroid->setType(ENTITY_ASTEROID);
		Sprite* asteroidSprite = new Sprite(asteroid->getPos(), asteroid->getRadius() * 2, asteroid->getRadius() * 2, asteroid->getAngle(), texAsteroid);
		asteroid->setSprite(asteroidSprite);
		graphicsEngine->pushSprite(asteroidSprite);
		ComponentMovable *c_Movable = new ComponentMovable();
		c_Movable->setOwner(asteroid);
		c_Movable->setVel(vmake(CORE_FRand(-asteroid_max_speed, +asteroid_max_speed), CORE_FRand(-asteroid_max_speed, +asteroid_max_speed)));
		asteroid->addComponent(c_Movable);
		ComponentCollisionable *c_AsteroidCollision = new ComponentCollisionable();
		c_AsteroidCollision->setOwner(asteroid);
		asteroid->addComponent(c_AsteroidCollision);
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
	Sprite* sprite;
	// Render backgground
	for (int i = 0; i <= SCR_WIDTH / bkgWidth; i++)
		for (int j = 0; j <= SCR_HEIGHT / bkgHeight; j++)
			CORE_RenderCenteredSprite(vmake(i * bkgWidth, j * bkgHeight), vmake(bkgHeight, bkgWidth), texSpaceBkg);



	for (auto entityIt = entities.begin(); entityIt != entities.end(); ++entityIt) {
		sprite = (*entityIt)->getSprite();
		if (sprite) {
			if ((*entityIt)->getType() == ENTITY_ASTEROID) {
				//CORE_RenderCenteredSprite((*entityIt)->getPos(), vmake((*entityIt)->getRadius() * 2.f, (*entityIt)->getRadius() * 2.f), (*entityIt)->getGfx());
				CORE_RenderCenteredSprite(sprite->getPos(), vmake((*entityIt)->getRadius() * 2.f, (*entityIt)->getRadius() * 2.f), sprite->getGfx());
			}
			else if ((*entityIt)->getType() == ENTITY_STATION) {
				//CORE_RenderCenteredSprite((*entityIt)->getPos(), vmake(stationWidth, stationHeight), (*entityIt)->getGfx());
				CORE_RenderCenteredSprite(sprite->getPos(), vmake(sprite->getWidth(), sprite->getHeight()), sprite->getGfx());
			}
			else if ((*entityIt)->getType() == ENTITY_PLAYER) {
				//CORE_RenderCenteredRotatedSprite((*entityIt)->getPos(), vmake(playerWidth, playerHeight), (*entityIt)->getAngle(), (*entityIt)->getGfx());
				CORE_RenderCenteredRotatedSprite(sprite->getPos(), vmake(sprite->getWidth(), sprite->getHeight()), sprite->getAngle(), sprite->getGfx());
			}
		}
	}
	


	SYS_Show();
}

void Game::run() {
	appManager->notPaused();
	for (auto entityIt = entities.begin(); entityIt != entities.end(); ++entityIt) {
		(*entityIt)->update();
	}
	checkPlayerCollision();
	if(!playerCollision)
		checkPlayerWin();

}

void Game::sendMessage(Message *msg) {

	for (auto entityIt = entities.begin(); entityIt != entities.end(); ++entityIt) {
		(*entityIt)->receiveMessage(msg);
	}

	//MESSAGES NOT FOR ENTITIES
	receiveNotEntityMessages(msg);
}

void Game::receiveNotEntityMessages(Message *msg) 
{
	Message *msg_rec = dynamic_cast<OMessage*>(msg);
	if (msg_rec) {
		//pause menu
		appManager->pause();
		appManager->switchMode(MODE_PAUSE_MENU);
		OutputDebugStringA("Game Paused!");
	}

}

void Game::checkPlayerCollision() {

	if (playerCollision) {
		appManager->switchMode(MODE_GAMEOVER);
	}

}

void Game::checkPlayerWin() {

	if (playerWin) {
		appManager->switchMode(MODE_WIN);
	}

}

