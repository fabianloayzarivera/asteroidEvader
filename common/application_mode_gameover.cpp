#include "stdafx.h"
#include "application_mode_gameover.h"

ApplicationModeGameOver::ApplicationModeGameOver() {
	texGameOver = CORE_LoadPNG("../data/asteroid.png", false);
	bkgHeight = 256;
	bkgWidth = 256;
}


void ApplicationModeGameOver::render() {
	// Render
	glClear(GL_COLOR_BUFFER_BIT);

	// Render Player
	CORE_RenderCenteredRotatedSprite(vmake(0,0), vmake(bkgWidth, bkgHeight),0 , texGameOver);

	SYS_Show();		
	

}