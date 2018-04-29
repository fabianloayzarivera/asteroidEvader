#include "stdafx.h"
#include "application_mode_pause_menu.h"
#include "application_manager.h"
#include "language_manager.h"
#include "globals.h"

#define MARGIN 35;

ApplicationModePauseMenu::ApplicationModePauseMenu() {
	texWin = CORE_LoadPNG("../data/pause.png", false);
	texMark = CORE_LoadPNG("../data/mark.png", false);
	insertOption("MENU_RESUME", MODE_GAME); 
	insertOption("MENU_MAIN_MENU", MODE_NULL);

	optionSelected = 0;
}

void ApplicationModePauseMenu::insertOption(const char* name, appModeId mode)
{

	if (options.size() > 0)
	{
		int newId = options.size();
		Option newOption(newId, name, mode);
		options.push_back(newOption);
	}
	else
	{
		Option newOption(0, name, mode);
		options.push_back(newOption);

	}
}

void ApplicationModePauseMenu::render() {
	// Render

	CORE_RenderCenteredRotatedSprite(vmake(SCR_WIDTH / 2, SCR_HEIGHT / 2.25), vmake(SCR_WIDTH/2, SCR_HEIGHT/3), 0, texWin);
	int pos = MARGIN;
	int posMark = pos - 7 + optionSelected * MARGIN;

	for (auto optionIt = options.begin(); optionIt != options.end(); ++optionIt) {
		FONT_DrawString(vmake(SCR_WIDTH / 2 - 5 * 16, SCR_HEIGHT / 2 - pos), languageManager->getString((*optionIt).name));
		pos += MARGIN;
	}
	CORE_RenderCenteredSprite(vmake(SCR_WIDTH / 2 - 6 * 16, SCR_HEIGHT / 2 - posMark), vmake(15, 15), texMark);

	SYS_Show();


}

void ApplicationModePauseMenu::receiveMessage(Message *msg) {
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
			if (optionSelected >= options.size())
				optionSelected = options.size() - 1;
		}
	}

	Message *msg_rec = dynamic_cast<ReturnMessage*>(msg);
	if (msg_rec) {
		OutputDebugStringA("Return!");
		//Execute Option Selected!
		if (options[optionSelected].modeId != MODE_NULL) {
			
			appManager->switchMode(options[optionSelected].modeId);
		}
		else
		{
			if (strcmp(options[optionSelected].name, "MENU_MAIN_MENU") == 0) 
			{
				appManager->notPaused();
				appManager->killGame();
				appManager->switchMode(MODE_MAIN_MENU);
			}
				
		}

	}


}

