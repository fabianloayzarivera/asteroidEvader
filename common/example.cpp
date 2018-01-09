#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include <time.h>
//-----------------------------------------------------------------------------
struct Asteroid
{
  vec2   pos;
  vec2   vel;
  GLuint gfx;
  float  radius;
};

struct Player
{
	vec2   pos;
	vec2   vel;
	float  angle;
	GLuint gfx;
	float  radius;
};

struct Station
{
	vec2   pos;
	//vec2   vel;
	GLuint gfx;
	float  radius;
};

#define NUM_ASTEROIDS_DEFAULT 3
#define MAX_ASTEROID_SPEED 8.f
#define PLAYER_MOVEMENT_SPEED_DEFAULT 8.f
#define PLAYER_ROTATION_SPEED_DEFAULT 0.05f

Asteroid asteroids[NUM_ASTEROIDS_DEFAULT];
Player player;
Station station;

//-----------------------------------------------------------------------------
int Main(void)
{
  FONT_Init();
  srand(time(NULL));
  // Load textures

  GLuint texAsteroid   = CORE_LoadPNG("../data/asteroid.png"		 , false);
  GLuint texSpaceBkg   = CORE_LoadPNG("../data/space_bkg2.png", false);
  GLuint texStation    = CORE_LoadPNG("../data/deathStar.png", false);
  GLuint texPlayer	   = CORE_LoadPNG("../data/space_ship.png", false);


  float bkgHeight = 256;
  float bkgWidth  = 256;

  float playerHeight = 45;
  float playerWidth = 45;
  int angleFactorX = 1;
  int angleFactorY = 1;

  float stationWidth = 125;
  float stationHeight = 125;

  // Init game state
  for (int i = 0; i < NUM_ASTEROIDS_DEFAULT; i++)
  {
    asteroids[i].pos = vmake(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
    asteroids[i].vel = vmake(CORE_FRand(-MAX_ASTEROID_SPEED, +MAX_ASTEROID_SPEED), CORE_FRand(-MAX_ASTEROID_SPEED, +MAX_ASTEROID_SPEED));
	asteroids[i].radius = CORE_FRand(14.f, 100.f);
	asteroids[i].gfx = texAsteroid;
   
  }

  player.vel = vmake(PLAYER_MOVEMENT_SPEED_DEFAULT, PLAYER_MOVEMENT_SPEED_DEFAULT);
  player.pos = vmake(SCR_WIDTH - playerWidth, playerHeight);
  player.radius = playerHeight > playerWidth ? playerHeight / 2 : playerWidth / 2;
  player.angle = 0;

  station.pos = vmake(stationWidth/2, SCR_HEIGHT - stationHeight/2);
  station.radius = stationHeight > stationWidth ? stationHeight / 2 : stationWidth / 2;

  // Set up rendering
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping
  glClearColor( 0.0f, 0.1f, 0.3f, 0.0f );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho( 0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  while (!SYS_GottaQuit())
  {
    // Render
    glClear( GL_COLOR_BUFFER_BIT );

    // Render backgground
    for (int i = 0; i <= SCR_WIDTH/bkgWidth; i++)
      for (int j = 0; j <= SCR_HEIGHT/bkgHeight; j++)
        CORE_RenderCenteredSprite(vmake(i * bkgWidth , j * bkgHeight ), vmake(bkgHeight, bkgWidth), texSpaceBkg);

    // Render balls
    for (int i = 0; i < NUM_ASTEROIDS_DEFAULT; i++)
      CORE_RenderCenteredSprite(asteroids[i].pos, vmake(asteroids[i].radius * 2.f, asteroids[i].radius * 2.f), asteroids[i].gfx);

	// Render Player
	CORE_RenderCenteredRotatedSprite(player.pos, vmake(playerWidth, playerHeight), player.angle, texPlayer);

	// Render Station
	CORE_RenderCenteredSprite(station.pos, vmake(stationWidth, stationHeight), texStation);
    // Text
    //FONT_DrawString(vmake(SCR_WIDTH/2 - 6*16, 16), "HELLO WORLD!");
	
   
    SYS_Show();

	// Move Player
	if (SYS_KeyPressed(SYS_KEY_UP)) {
		vec2 oldPosPlayer = player.pos;
		vec2 vectorMove = vmake(player.vel.x * player.angle * angleFactorX, player.vel.y); //CHANGE THE FACTOR EACH DEPENDING ON THE ANGLE!!
		vec2 newPosPlayer = vadd(oldPosPlayer, vectorMove);

		player.pos = newPosPlayer;
	}

	// Rotate Player
	if (SYS_KeyPressed(SYS_KEY_LEFT)) {
		player.angle += PLAYER_ROTATION_SPEED_DEFAULT;
		if (player.angle >= 2 * M_PIf)
			player.angle = 0;

		if (player.angle > 0 && player.angle <= M_PIf)
			angleFactorX = -1;
		else
			angleFactorX = 1;
		/*std::string angle = std::to_string(player.angle* 57.2958);
		OutputDebugStringA(angle.c_str());
		OutputDebugStringA("\n");*/
	}

	if (SYS_KeyPressed(SYS_KEY_RIGHT)) {
		player.angle -= PLAYER_ROTATION_SPEED_DEFAULT;
		if (player.angle <= -2 * M_PIf)
			player.angle = 0;
		/*std::string angle = std::to_string(player.angle * 57.2958);
		OutputDebugStringA(angle.c_str());
		OutputDebugStringA("\n");*/
	}


    // Run Asteroids
    for (int i = 0; i < NUM_ASTEROIDS_DEFAULT; i++)
    {
      vec2 oldpos = asteroids[i].pos;
      vec2 newpos = vadd(oldpos, asteroids[i].vel);
	  
      bool collision = false;
      int colliding_ball = -1;
      for (int j = 0; j < NUM_ASTEROIDS_DEFAULT; j++)
      {
        if (i != j)
        {
          float limit2 = (asteroids[i].radius + asteroids[j].radius) * (asteroids[i].radius + asteroids[j].radius);
          if (vlen2(vsub(oldpos, asteroids[j].pos)) > limit2 && vlen2(vsub(newpos, asteroids[j].pos)) <= limit2)
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
        asteroids[i].vel = vscale(asteroids[i].vel, -1.f); //Change the collision algorithm
        asteroids[colliding_ball].vel = vscale(asteroids[colliding_ball].vel, -1.f);
      }

      // Rebound on margins
      if (asteroids[i].vel.x > 0.0)
      {
        if (asteroids[i].pos.x > SCR_WIDTH)
          asteroids[i].vel.x *= -1.0;
      } else {
        if (asteroids[i].pos.x < 0)
          asteroids[i].vel.x *= -1.0;
      }
      if (asteroids[i].vel.y > 0.0)
      {
        if (asteroids[i].pos.y > SCR_HEIGHT)
          asteroids[i].vel.y *= -1.0;
      } else {
        if (asteroids[i].pos.y < 0)
          asteroids[i].vel.y *= -1.0;
      }
    }
   
    // Keep system running
    SYS_Pump();
    SYS_Sleep(17);
  }

  CORE_UnloadPNG(texSpaceBkg);
  FONT_End();

  return 0;
}
