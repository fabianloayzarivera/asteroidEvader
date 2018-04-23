#pragma once
#include "sys.h"
#include "core.h"
#include "font.h"
#include <time.h>
#include "entity.h"
#include "entity_asteroid.h"
#include "entity_player.h"
#include "entity_station.h"
#include "component_movable.h"
#include "component_player_controller.h"
#include "component_collisionable.h"
#include "sprite.h"
#include <vector>
#include "message.h"

#define NUM_ASTEROIDS_DEFAULT 4
#define MAX_ASTEROID_SPEED 8.f
#define PLAYER_MOVEMENT_SPEED_DEFAULT 8.f
#define PLAYER_ROTATION_SPEED_DEFAULT 0.085f

using namespace std;

class Game {
private:
	
	vector<Entity*> entities;
	
	GLuint texAsteroid;
	GLuint texSpaceBkg;
	GLuint texStation;
	GLuint texPlayer;
	GLuint texExplosion;
	float  bkgHeight;
	float  bkgWidth;
	float  playerHeight;
	float  playerWidth;
	bool   playerCollision;
	bool   playerWin;
	float  stationWidth;
	float  stationHeight;
	float  player_movement_speed;
	float  player_rotation_speed;
	int    asteroid_num;
	float  asteroid_max_speed;
	string levelName;

	void checkPlayerCollision();
	void checkPlayerWin();
public:
	Game(int level);
	~Game();
	void run();
	void sendMessage(Message *msg);
	void receiveNotEntityMessages(Message *msg);
	void render();
	void setPlayerCollision(bool c) { playerCollision = c; }
	bool getPlayerCollision() { return playerCollision; }
	void setPlayerWin(bool c) { playerWin = c; }
	bool getPlayerWin() { return playerWin; }
	vector<Entity*> getEntities() { return entities; }


};
