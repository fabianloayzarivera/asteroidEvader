#include "stdafx.h"
#include "application_mode_option_menu.h"
#include "application_manager.h"
#include "globals.h"
ApplicationModeOptionMenu::ApplicationModeOptionMenu() {
	texWin = CORE_LoadPNG("../data/main_menu.png", false);

}


void ApplicationModeOptionMenu::render() {
	// Render
	glClear(GL_COLOR_BUFFER_BIT);

	// Render Player
	CORE_RenderCenteredRotatedSprite(vmake(SCR_WIDTH / 2, SCR_HEIGHT / 2), vmake(SCR_WIDTH, SCR_HEIGHT), 0, texWin);
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 5 * 16, SCR_HEIGHT / 2),      "AUDIO SWITCH (A)");
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 5 * 16, SCR_HEIGHT / 2 - 25), "LANGUAGE     (E)");
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 5 * 16, SCR_HEIGHT / 2 - 50), "BACK         (B)");
	SYS_Show();


}


void ApplicationModeOptionMenu::receiveMessage(Message *msg) {
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

	Message *msg_rec = dynamic_cast<AMessage*>(msg);
	if (msg_rec) {
		//SWITCH AUDIO
		appManager->switchAudio();
		OutputDebugStringA("Audio Switched!");
	}

	msg_rec = dynamic_cast<EMessage*>(msg);
	if (msg_rec) {
		
	}

	msg_rec = dynamic_cast<BMessage*>(msg);
	if (msg_rec) {
		appManager->switchMode(MODE_MAIN_MENU);
	}


	

}