#pragma once
#include "application_mode_game.h"

enum appModeId {MODE_GAME, MODE_MENU};

class ApplicationManager {
private:
	ApplicationMode* activeMode;
public:
	ApplicationManager() {}
	void switchMode(appModeId id) {
		switch (id)
		{
		case MODE_GAME:
			activeMode = new ApplicationModeGame();
			break;
		case MODE_MENU:
			break;
		default:
			break;
		}
	}
	void run() { activeMode->run(); }
	void render() { activeMode->render(); }
	void processInput() { activeMode->processInput(); }

};
