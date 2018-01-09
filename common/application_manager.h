#pragma once
#include "application_mode_game.h"

enum appModeId {MODE_IDLE, MODE_GAME, MODE_MENU};

class ApplicationManager {
private:
	ApplicationMode* activeMode;
	appModeId activeModeId;
public:
	ApplicationManager() { activeModeId = MODE_IDLE; }
	void switchMode(appModeId id) {

		if (id != activeModeId) {
			switch (id)
			{
			case MODE_GAME:
				activeMode = new ApplicationModeGame();
				activeModeId = MODE_GAME;
				break;
			case MODE_MENU:
				break;
			default:
				break;
			}
		}
	}
	void run() { activeMode->run(); }
	void render() { activeMode->render(); }
	void processInput() { activeMode->processInput(); }

};
