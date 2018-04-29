#include "stdafx.h"
#include "application_mode_gameover.h"
#include "application_manager.h"
#include "language_manager.h"
#include "globals.h"
ApplicationModeGameOver::ApplicationModeGameOver() {
	texGameOver = CORE_LoadPNG("../data/game_over_2.png", false);

}


void ApplicationModeGameOver::render() {
	// Render
	glClear(GL_COLOR_BUFFER_BIT);
	CORE_RenderCenteredRotatedSprite(vmake(SCR_WIDTH/2,SCR_HEIGHT/2), vmake(SCR_WIDTH , SCR_HEIGHT ),0 , texGameOver);
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 15 * 16, SCR_HEIGHT / 2 - 100), languageManager->getString("MENU_RESTART"));

	SYS_Show();		
	

}

void ApplicationModeGameOver::receiveMessage(Message *msg) {	

	Message *msg_rec = dynamic_cast<ReturnMessage*>(msg);
	if (msg_rec) {
		OutputDebugStringA("Return!");
		//Execute Option Selected!
		appManager->switchMode(MODE_GAME);
		
	}

}