#pragma once
#include "application_mode_game.h"
#include "application_mode_gameover.h"

enum appModeId {MODE_IDLE, MODE_GAME, MODE_MENU, MODE_GAMEOVER};

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
			case MODE_GAMEOVER:
				activeMode = new ApplicationModeGameOver();
				activeModeId = MODE_GAMEOVER;
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
