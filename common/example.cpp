#include "stdafx.h"
#include "game.h"
//-----------------------------------------------------------------------------

int Main(void)
{
  FONT_Init();
  srand(time(NULL));
  
  Game game;
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
	game.render();
	game.processInput();
	game.run();

    // Keep system running
    SYS_Pump();
    SYS_Sleep(17);
  }

  FONT_End();

  return 0;
}

