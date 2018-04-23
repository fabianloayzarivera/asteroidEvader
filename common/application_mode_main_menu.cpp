#include "stdafx.h"
#include "application_mode_main_menu.h"
#include "application_manager.h"
#include "globals.h"
ApplicationModeMainMenu::ApplicationModeMainMenu() {
	texWin = CORE_LoadPNG("../data/main_menu.png", false);

}


void ApplicationModeMainMenu::render() {
	// Render
	glClear(GL_COLOR_BUFFER_BIT);

	// Render Player
	CORE_RenderCenteredRotatedSprite(vmake(SCR_WIDTH / 2, SCR_HEIGHT / 2), vmake(SCR_WIDTH, SCR_HEIGHT), 0, texWin);
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 5 * 16, SCR_HEIGHT / 2 - 25), "PLAY    (P)");
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 5 * 16, SCR_HEIGHT / 2 - 50), "OPTIONS (O)");
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 5 * 16, SCR_HEIGHT / 2 - 75), "LEVELS  (L)");
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 5 * 16, SCR_HEIGHT / 2 - 125),"QUIT    (Q)");
	SYS_Show();


}


void ApplicationModeMainMenu::receiveMessage(Message *msg) {
	UpMessage *upMsg = dynamic_cast<UpMessage*>(msg);
	if (upMsg) {
		if (upMsg->up) {
			OutputDebugStringA("UP!");
		}
	}

	DownMessage *downMsg = dynamic_cast<DownMessage*>(msg);
	if (downMsg) {
		if (downMsg->down) {
			OutputDebugStringA("DOWN!");
		}
	}

	Message *msg_rec = dynamic_cast<PMessage*>(msg);
	if (msg_rec) {
		appManager->switchMode(MODE_GAME);
	}

	msg_rec = dynamic_cast<OMessage*>(msg);
	if (msg_rec) {
		appManager->switchMode(MODE_OPTION_MENU);
	}

	msg_rec = dynamic_cast<LMessage*>(msg);
	if (msg_rec) {
		appManager->switchMode(MODE_LEVEL_MENU);
	}

	msg_rec = dynamic_cast<QMessage*>(msg);
	if (msg_rec) {
		exit(0);
	}
	

}