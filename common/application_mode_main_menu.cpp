#include "stdafx.h"
#include "application_mode_main_menu.h"
#include "application_manager.h"
#include "language_manager.h"
#include "globals.h"

#define MARGIN 35;

ApplicationModeMainMenu::ApplicationModeMainMenu() {

	texWin = CORE_LoadPNG("../data/main_menu.png", false);
	texMark = CORE_LoadPNG("../data/mark.png", false);
	insertOption("MENU_PLAY", MODE_GAME);
	insertOption("MENU_OPTIONS", MODE_OPTION_MENU);
	insertOption("MENU_LEVELS", MODE_LEVEL_MENU);
	insertOption("MENU_QUIT", MODE_NULL);

	
}

void ApplicationModeMainMenu::insertOption(const char* name, appModeId mode)
{
	
	if (options.size() > 0) 
	{
		int newId = options.size();
		Option newOption(newId, name,mode);
		options.push_back(newOption);
	}
	else 
	{
		Option newOption(0, name, mode);
		options.push_back(newOption);

	}
}

void ApplicationModeMainMenu::render() {
	// Render
	glClear(GL_COLOR_BUFFER_BIT);

	// Render Player
	CORE_RenderCenteredRotatedSprite(vmake(SCR_WIDTH / 2, SCR_HEIGHT / 2), vmake(SCR_WIDTH, SCR_HEIGHT), 0, texWin);
	int pos = MARGIN;
	int posMark = pos - 7 + optionSelected * MARGIN;

	for (auto optionIt = options.begin(); optionIt != options.end(); ++optionIt) {
		FONT_DrawString(vmake(SCR_WIDTH / 2 - 5 * 16, SCR_HEIGHT / 2 - pos), languageManager->getString((*optionIt).name));
		pos += MARGIN;
	}
	/*FONT_DrawString(vmake(SCR_WIDTH / 2 - 5 * 16, SCR_HEIGHT / 2 - 25), languageManager->getString("MENU_PLAY"));
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 5 * 16, SCR_HEIGHT / 2 - 50), languageManager->getString("MENU_OPTIONS"));
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 5 * 16, SCR_HEIGHT / 2 - 75), languageManager->getString("MENU_LEVELS"));
	FONT_DrawString(vmake(SCR_WIDTH / 2 - 5 * 16, SCR_HEIGHT / 2 - 125),languageManager->getString("MENU_QUIT"));*/

	CORE_RenderCenteredSprite(vmake(SCR_WIDTH / 2 - 6 * 16 , SCR_HEIGHT / 2 - posMark), vmake(15, 15), texMark);
	SYS_Show();


}

void ApplicationModeMainMenu::receiveMessage(Message *msg) {
	UpMessage *upMsg = dynamic_cast<UpMessage*>(msg);
	if (upMsg) {
		if (upMsg->up) {
			optionSelected--;
			if (optionSelected < 0)
				optionSelected = 0;
		}
	}

	DownMessage *downMsg = dynamic_cast<DownMessage*>(msg);
	if (downMsg) {
		if (downMsg->down) {
			optionSelected++;
			if (optionSelected >=  options.size())
				optionSelected = options.size() -1 ;
		}
	}	

	Message *msg_rec = dynamic_cast<ReturnMessage*>(msg);
	if (msg_rec) {
		OutputDebugStringA("Return!");
		//Execute Option Selected!
		if (options[optionSelected].modeId != MODE_NULL)
			appManager->switchMode(options[optionSelected].modeId);
		else
		{
			if (strcmp(options[optionSelected].name, "MENU_QUIT") == 0)
				exit(0);
		}

	}

	/*Message *msg_rec = dynamic_cast<PMessage*>(msg);
	if (msg_rec) {
		appManager->switchMode(MODE_GAME);
	}*/

	/*msg_rec = dynamic_cast<OMessage*>(msg);
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
	}*/
	

}