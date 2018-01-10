#pragma once
#include "sys.h"
#include "core.h"
#include "font.h"
#include <time.h>
#include "entity_asteroid.h"
#include "entity_player.h"
#include "entity_station.h"
#define NUM_ASTEROIDS_DEFAULT 4
#define MAX_ASTEROID_SPEED 8.f
#define PLAYER_MOVEMENT_SPEED_DEFAULT 8.f
#define PLAYER_ROTATION_SPEED_DEFAULT 0.085f

//struct Asteroid
//{
//	vec2   pos;
//	vec2   vel;
//	GLuint gfx;
//	float  radius;
//};
//
//struct Player
//{
//	vec2   pos;
//	vec2   vel;
//	float  angle;
//	GLuint gfx;
//	float  radius;
//};
//
//struct Station
//{
//	vec2   pos;
//	GLuint gfx;
//	float  radius;
//};

class Game {
private:
	Player player;
	Station station;
	Asteroid asteroids[NUM_ASTEROIDS_DEFAULT];
	GLuint texAsteroid;
	GLuint texSpaceBkg;
	GLuint texStation;
	GLuint texPlayer;
	GLuint texExplosion;
	float bkgHeight;
	float bkgWidth;
	float playerHeight;
	float playerWidth;
	int angleFactorX;
	int angleFactorY;
	bool playerCollision;
	bool playerWin;
	float stationWidth;
	float stationHeight;

	void movePlayer();
	void rotatePlayerLeft();
	void rotatePlayerRight();
	void runAsteroids();
public:
	Game();
	~Game();
	void run();
	void render();
	void processInput();


};
