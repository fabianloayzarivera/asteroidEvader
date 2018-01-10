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
	angleFactorX = 1;
	angleFactorY = 1;
	playerCollision = false;
	playerWin = false;

	stationWidth = 125;
	stationHeight = 125;

	int asteroidsCreated = 0;
	for (int i = 0; i < NUM_ASTEROIDS_DEFAULT; i++)
	{
		asteroids[i].pos = vmake(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
		asteroids[i].radius = CORE_FRand(14.f, 100.f);
		for (int j = 0; j < asteroidsCreated; j++) {
			while (collideCircles(asteroids[i].pos, asteroids[i].radius, asteroids[j].pos, asteroids[j].radius)) {
				asteroids[i].pos = vmake(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
			}
		}
		asteroids[i].vel = vmake(CORE_FRand(-MAX_ASTEROID_SPEED, +MAX_ASTEROID_SPEED), CORE_FRand(-MAX_ASTEROID_SPEED, +MAX_ASTEROID_SPEED));
		asteroids[i].gfx = texAsteroid;
		asteroidsCreated++;

	}

	player.vel = vmake(PLAYER_MOVEMENT_SPEED_DEFAULT, PLAYER_MOVEMENT_SPEED_DEFAULT);
	player.pos = vmake(SCR_WIDTH - playerWidth, playerHeight);
	player.radius = playerHeight > playerWidth ? playerHeight / 2 : playerWidth / 2;
	player.gfx = texPlayer;
	player.angle = 0;

	station.pos = vmake(stationWidth / 2, SCR_HEIGHT - stationHeight / 2);
	station.radius = stationHeight > stationWidth ? stationHeight / 2 : stationWidth / 2;

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

	
	// Render Player
	CORE_RenderCenteredRotatedSprite(player.pos, vmake(playerWidth, playerHeight), player.angle, player.gfx);

	// Render balls
	for (int i = 0; i < NUM_ASTEROIDS_DEFAULT; i++)
		CORE_RenderCenteredSprite(asteroids[i].pos, vmake(asteroids[i].radius * 2.f, asteroids[i].radius * 2.f), asteroids[i].gfx);

	// Render Station
	CORE_RenderCenteredSprite(station.pos, vmake(stationWidth, stationHeight), texStation);
	// Text

	if (playerCollision)
		FONT_DrawString(vmake(SCR_WIDTH / 2 - 6 * 16, 16), "GAME OVER!");
	if (playerWin)
		FONT_DrawString(vmake(SCR_WIDTH / 2 - 12 * 16, 16), "CONGRATULATIONS YOU WIN!");

	SYS_Show();
}

void Game::run() {

	runAsteroids();
	if (playerCollision) {
		//appManager->switchMode(MODE_GAMEOVER);
	}

}

void Game::runAsteroids() {
	// Run Asteroids
	for (int i = 0; i < NUM_ASTEROIDS_DEFAULT; i++)
	{
		vec2 oldpos = asteroids[i].pos;
		vec2 newpos = vadd(oldpos, asteroids[i].vel);

		bool collision = false;
		int colliding_ball = -1;

		//////////COLLISION WITH OTHER ASTEROIDS////////////

		for (int j = 0; j < NUM_ASTEROIDS_DEFAULT; j++)
		{
			if (i != j)
			{
				float limit2 = (asteroids[i].radius + asteroids[j].radius) * (asteroids[i].radius + asteroids[j].radius);
				if (vlen2(vsub(newpos, asteroids[j].pos)) <= limit2)
				{
					collision = true;
					colliding_ball = j;
					break;
				}
			}
		}

		if (!collision)
			asteroids[i].pos = newpos;
		else
		{
			// Rebound!
			//asteroids[i].vel = vscale(asteroids[i].vel, -1.f); //Change the collision algorithm
			if (asteroids[i].vel.x > 0.0)		
					asteroids[i].vel.x *= -1.0;			
			if (asteroids[i].vel.y < 0.0)			
					asteroids[i].vel.y *= -1.0;			
			
			//asteroids[colliding_ball].vel = vscale(asteroids[colliding_ball].vel, -1.f);
			if (asteroids[colliding_ball].vel.x < 0.0) {
				asteroids[colliding_ball].vel.x *= -1.0;
			}
			if (asteroids[colliding_ball].vel.y > 0.0) {
				asteroids[colliding_ball].vel.y *= -1.0;
			}
			
		}

		//////////COLLISION WITH PLAYER////////////

		float limitWithPlayer = (asteroids[i].radius + player.radius) * (asteroids[i].radius + player.radius);
		if (vlen2(vsub(newpos, player.pos)) <= limitWithPlayer)
		{
			playerCollision = true;
			OutputDebugStringA("DEAD!!");
			OutputDebugStringA("\n");
			player.gfx = texExplosion;
			FONT_DrawString(vmake(SCR_WIDTH / 2 - 6 * 16, 16), "GAME OVER!");
		}

		
		// Rebound on margins
		if (asteroids[i].vel.x > 0.0)
		{
			if (asteroids[i].pos.x + asteroids[i].radius > SCR_WIDTH)
				asteroids[i].vel.x *= -1.0;
		}
		else {
			if (asteroids[i].pos.x - asteroids[i].radius< 0)
				asteroids[i].vel.x *= -1.0;
		}
		if (asteroids[i].vel.y > 0.0)
		{
			if (asteroids[i].pos.y + asteroids[i].radius> SCR_HEIGHT)
				asteroids[i].vel.y *= -1.0;
		}
		else {
			if (asteroids[i].pos.y - asteroids[i].radius< 0)
				asteroids[i].vel.y *= -1.0;
		}
	}
}
void Game::processInput() {
	// Move Player
	if (SYS_KeyPressed(SYS_KEY_UP)) {
		movePlayer();
	}
	// Rotate Player
	if (SYS_KeyPressed(SYS_KEY_LEFT)) {
		rotatePlayerLeft();
	}

	if (SYS_KeyPressed(SYS_KEY_RIGHT)) {
		rotatePlayerRight();
	}

}

void Game::movePlayer() {
	vec2 oldPosPlayer = player.pos;
	float trueAngle = player.angle + M_PIf / 2;
	float angleFactorX = cos(trueAngle);
	float angleFactorY = sin(trueAngle);
	vec2 vectorMove = vmake(player.vel.x * angleFactorX, player.vel.y * angleFactorY);
	vec2 newPosPlayer = vadd(oldPosPlayer, vectorMove);
	player.pos = newPosPlayer;

	if (collideCircles(player.pos, player.radius, station.pos, station.radius)) {
		playerWin = true;
	}
}

void Game::rotatePlayerLeft() {
	player.angle += PLAYER_ROTATION_SPEED_DEFAULT;
	if (player.angle >= 2 * M_PIf)
		player.angle = 0;

}

void Game::rotatePlayerRight() {
	player.angle -= PLAYER_ROTATION_SPEED_DEFAULT;
	if (player.angle <= 0)
		player.angle = 2 * M_PIf;

}