#pragma once
#include "application_mode_game.h"
#include "application_mode_win.h"
#include "application_mode_gameover.h"
#include "application_mode_main_menu.h"
#include "application_mode_option_menu.h"

enum appModeId {MODE_IDLE, MODE_GAME, MODE_PAUSE_MENU, MODE_OPTION_MENU, MODE_WIN, MODE_GAMEOVER, MODE_MAIN_MENU};


class ApplicationManager {
private:
	ApplicationMode* activeMode;
	appModeId		 activeModeId;
	bool			 audioState;
public:
	ApplicationManager() { activeModeId = MODE_IDLE; audioState = true; }
	void switchAudio() { audioState = (!audioState); }
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
			case MODE_MAIN_MENU:
				delete(activeMode);
				if(game)
					delete(game);
				activeMode = new ApplicationModeMainMenu();
				activeModeId = MODE_MAIN_MENU;
				break;
			case MODE_OPTION_MENU:
				delete(activeMode);
				if (game)
					delete(game);
				activeMode = new ApplicationModeOptionMenu();
				activeModeId = MODE_OPTION_MENU;
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
	void sendMessage(Message *msg) { activeMode->sendMessage(msg); }

};
