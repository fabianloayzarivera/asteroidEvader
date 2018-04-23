#include "stdafx.h"
#include "application_mode_level_menu.h"
#include "application_manager.h"
#include "language_manager.h"
#include "globals.h"

#define MARGIN 35;

ApplicationModeLevelMenu::ApplicationModeLevelMenu() {
	texWin = CORE_LoadPNG("../data/main_menu.png", false);
	texMark = CORE_LoadPNG("../data/mark.png", false);
	insertOption("MENU_LEVEL_EARTH", MODE_GAME); //CHANGE!!
	insertOption("MENU_LEVEL_MARS", MODE_GAME); //CHANGE!!
	insertOption("MENU_LEVEL_JUPITER", MODE_GAME);
	insertOption("MENU_BACK", MODE_MAIN_MENU);

	optionSelected = 0;
}

void ApplicationModeLevelMenu::insertOption(const char* name, appModeId mode)
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

void ApplicationModeLevelMenu::render() {
	// Render
	glClear(GL_COLOR_BUFFER_BIT);

	CORE_RenderCenteredRotatedSprite(vmake(SCR_WIDTH / 2, SCR_HEIGHT / 2), vmake(SCR_WIDTH, SCR_HEIGHT), 0, texWin);
	int pos = MARGIN;
	int posMark = pos - 7 + optionSelected * MARGIN;

	for (auto optionIt = options.begin(); optionIt != options.end(); ++optionIt) {
		FONT_DrawString(vmake(SCR_WIDTH / 2 - 5 * 16, SCR_HEIGHT / 2 - pos), languageManager->getString((*optionIt).name));
		pos += MARGIN;
	}
	CORE_RenderCenteredSprite(vmake(SCR_WIDTH / 2 - 6 * 16, SCR_HEIGHT / 2 - posMark), vmake(15, 15), texMark);

	SYS_Show();


}


void ApplicationModeLevelMenu::receiveMessage(Message *msg) {
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
		appManager->setLevel(optionSelected);
		appManager->switchMode(options[optionSelected].modeId);
	}

	
	

}