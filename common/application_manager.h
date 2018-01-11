#pragma once
#include "application_mode_game.h"
#include "application_mode_win.h"
#include "application_mode_gameover.h"

enum appModeId {MODE_IDLE, MODE_GAME, MODE_MENU, MODE_WIN, MODE_GAMEOVER};

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
				delete(activeMode);
				game = new Game();
				activeMode = new ApplicationModeGame();
				activeModeId = MODE_GAME;
				break;
			case MODE_MENU:
				break;
			case MODE_WIN:
				delete(activeMode);
				delete(game);
				activeMode = new ApplicationModeWin();
				activeModeId = MODE_WIN;
				break;
			case MODE_GAMEOVER:
				delete(activeMode);
				delete(game);
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
