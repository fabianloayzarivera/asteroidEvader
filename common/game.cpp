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
		asteroids[i].setPos( vmake(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));
		asteroids[i].setRadius( CORE_FRand(14.f, 100.f));
		for (int j = 0; j < asteroidsCreated; j++) {
			while (collideCircles(asteroids[i].getPos(), asteroids[i].getRadius(), asteroids[j].getPos(), asteroids[j].getRadius())) {
				asteroids[i].setPos( vmake(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));
			}
		}
		asteroids[i].setVel( vmake(CORE_FRand(-MAX_ASTEROID_SPEED, +MAX_ASTEROID_SPEED), CORE_FRand(-MAX_ASTEROID_SPEED, +MAX_ASTEROID_SPEED)));
		asteroids[i].setGfx( texAsteroid);
		asteroidsCreated++;

	}

	player.setVel(vmake(PLAYER_MOVEMENT_SPEED_DEFAULT, PLAYER_MOVEMENT_SPEED_DEFAULT));
	player.setPos( vmake(SCR_WIDTH - playerWidth, playerHeight));
	player.setRadius( playerHeight > playerWidth ? playerHeight / 2 : playerWidth / 2);
	player.setGfx(texPlayer);
	player.setAngle(0);

	station.setPos( vmake(stationWidth / 2, SCR_HEIGHT - stationHeight / 2));
	station.setRadius( stationHeight > stationWidth ? stationHeight / 2 : stationWidth / 2);

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
	CORE_RenderCenteredRotatedSprite(player.getPos(), vmake(playerWidth, playerHeight), player.getAngle(), player.getGfx());

	// Render balls
	for (int i = 0; i < NUM_ASTEROIDS_DEFAULT; i++)
		CORE_RenderCenteredSprite(asteroids[i].getPos(), vmake(asteroids[i].getRadius() * 2.f, asteroids[i].getRadius() * 2.f), asteroids[i].getGfx());

	// Render Station
	CORE_RenderCenteredSprite(station.getPos(), vmake(stationWidth, stationHeight), texStation);
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
		vec2 oldpos = asteroids[i].getPos();
		vec2 newpos = vadd(oldpos, asteroids[i].getVel());

		bool collision = false;
		int colliding_ball = -1;

		//////////COLLISION WITH OTHER ASTEROIDS////////////

		for (int j = 0; j < NUM_ASTEROIDS_DEFAULT; j++)
		{
			if (i != j)
			{
				float limit2 = (asteroids[i].getRadius() + asteroids[j].getRadius()) * (asteroids[i].getRadius() + asteroids[j].getRadius());
				if (vlen2(vsub(newpos, asteroids[j].getPos())) <= limit2)
				{
					collision = true;
					colliding_ball = j;
					break;
				}
			}
		}

		if (!collision)
			asteroids[i].setPos( newpos);
		else
		{
			// Rebound!
			//asteroids[i].vel = vscale(asteroids[i].vel, -1.f); //Change the collision algorithm
			if (asteroids[i].getVel().x > 0.0)
				asteroids[i].setVel(vmake(asteroids[i].getVel().x * -1.0, asteroids[i].getVel().y));
			if (asteroids[i].getVel().y < 0.0)
				asteroids[i].setVel(vmake(asteroids[i].getVel().x, asteroids[i].getVel().y * -1.0));
			
			//asteroids[colliding_ball].vel = vscale(asteroids[colliding_ball].vel, -1.f);
			if (asteroids[colliding_ball].getVel().x < 0.0) {
				asteroids[colliding_ball].setVel(vmake(asteroids[colliding_ball].getVel().x * -1.0, asteroids[colliding_ball].getVel().y));
			}
			if (asteroids[colliding_ball].getVel().y > 0.0) {
				asteroids[colliding_ball].setVel(vmake(asteroids[colliding_ball].getVel().x, asteroids[colliding_ball].getVel().y * -1.0));
			}
			
		}

		//////////COLLISION WITH PLAYER////////////

		float limitWithPlayer = (asteroids[i].getRadius() + player.getRadius()) * (asteroids[i].getRadius() + player.getRadius());
		if (vlen2(vsub(newpos, player.getPos())) <= limitWithPlayer)
		{
			playerCollision = true;
			OutputDebugStringA("DEAD!!");
			OutputDebugStringA("\n");
			player.setGfx(texExplosion);
			FONT_DrawString(vmake(SCR_WIDTH / 2 - 6 * 16, 16), "GAME OVER!");
		}

		
		// Rebound on margins
		if (asteroids[i].getVel().x > 0.0)
		{
			if (asteroids[i].getPos().x + asteroids[i].getRadius() > SCR_WIDTH)
				asteroids[i].setVel(vmake(asteroids[i].getVel().x * -1.0, asteroids[i].getVel().y));
		}
		else {
			if (asteroids[i].getPos().x - asteroids[i].getRadius()< 0)
				asteroids[i].setVel(vmake(asteroids[i].getVel().x * -1.0, asteroids[i].getVel().y));
		}
		if (asteroids[i].getVel().y > 0.0)
		{
			if (asteroids[i].getPos().y + asteroids[i].getRadius()> SCR_HEIGHT)
				asteroids[i].setVel(vmake(asteroids[i].getVel().x, asteroids[i].getVel().y * -1.0));
		}
		else {
			if (asteroids[i].getPos().y - asteroids[i].getRadius()< 0)
				asteroids[i].setVel(vmake(asteroids[i].getVel().x, asteroids[i].getVel().y * -1.0));
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
	vec2 oldPosPlayer = player.getPos();
	float trueAngle = player.getAngle() + M_PIf / 2;
	float angleFactorX = cos(trueAngle);
	float angleFactorY = sin(trueAngle);
	vec2 vectorMove = vmake(player.getVel().x * angleFactorX, player.getVel().y * angleFactorY);
	vec2 newPosPlayer = vadd(oldPosPlayer, vectorMove);
	player.setPos( newPosPlayer);

	if (collideCircles(player.getPos(), player.getRadius(), station.getPos(), station.getRadius())) {
		playerWin = true;
	}
}

void Game::rotatePlayerLeft() {
	player.setAngle(player.getAngle() + PLAYER_ROTATION_SPEED_DEFAULT);
	if (player.getAngle() >= 2 * M_PIf)
		player.setAngle( 0);

}

void Game::rotatePlayerRight() {
	player.setAngle(player.getAngle() - PLAYER_ROTATION_SPEED_DEFAULT);
	if (player.getAngle() <= 0)
		player.setAngle(2 * M_PIf);

}