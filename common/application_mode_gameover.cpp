#include "stdafx.h"
#include "application_mode_gameover.h"
#include "application_manager.h"
#include "globals.h"
ApplicationModeGameOver::ApplicationModeGameOver() {
	texGameOver = CORE_LoadPNG("../data/game_over.png", false);

}


void ApplicationModeGameOver::render() {
	// Render
	glClear(GL_COLOR_BUFFER_BIT);

	// Render Player
	CORE_RenderCenteredRotatedSprite(vmake(SCR_WIDTH/2,SCR_HEIGHT/2), vmake(SCR_WIDTH , SCR_HEIGHT ),0 , texGameOver);

	SYS_Show();		
	

}

void ApplicationModeGameOver::processInput() {
	if (SYS_KeyPressed(VK_RETURN)) {
		appManager->switchMode(MODE_GAME);
	}


}