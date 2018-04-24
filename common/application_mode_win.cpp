#include "stdafx.h"
#include "application_mode_win.h"
#include "application_manager.h"
#include "language_manager.h"
#include "globals.h"
ApplicationModeWin::ApplicationModeWin() {
	texWin = CORE_LoadPNG("../data/game_win.png", false);

}


void ApplicationModeWin::render() {
	// Render
	glClear(GL_COLOR_BUFFER_BIT);

	// Render Player
	CORE_RenderCenteredRotatedSprite(vmake(SCR_WIDTH / 2, SCR_HEIGHT / 2), vmake(SCR_WIDTH, SCR_HEIGHT), 0, texWin);
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 15 * 16, SCR_HEIGHT / 2 - 250), languageManager->getString("MENU_NEXT_LEVEL"));

	SYS_Show();


}

void ApplicationModeWin::receiveMessage(Message *msg) {


	Message *msg_rec = dynamic_cast<ReturnMessage*>(msg);
	if (msg_rec) {
		appManager->nextLevel();
		if (appManager->getLevel() < appManager->getLevelAmount())
			appManager->switchMode(MODE_GAME);
		else
			appManager->switchMode(MODE_MAIN_MENU);

	}




}

