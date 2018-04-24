#pragma once
#include "application_mode_game.h"
#include "application_mode_win.h"
#include "application_mode_gameover.h"
#include "application_mode_main_menu.h"
#include "application_mode_option_menu.h"
#include "application_mode_level_menu.h"
#include "application_mode_pause_menu.h"



class ApplicationManager {
private:
	ApplicationMode* activeMode;
	appModeId		 activeModeId;
	bool			 audioState;
	bool			 paused;
	int				 currentLevel;
	int              levelAmount;
public:
	ApplicationManager() { activeModeId = MODE_IDLE; audioState = true; currentLevel = 0; paused = false; levelAmount = 0; }
	void switchAudio() { audioState = (!audioState); }
	bool getAudioState() { return audioState; }
	int  getLevel() { return currentLevel; }
	void setLevel(int level) { currentLevel = level; }
	void setLevelAmount(int num) { levelAmount = num; }
	int getLevelAmount() { return levelAmount; }
	void nextLevel() { currentLevel++; }
	void pause() { paused = true; }
	void notPaused() { paused = false; }
	void killGame() { if(game)delete(game); }

	void switchMode(appModeId id) {

		if (id != activeModeId) {
			switch (id)
			{
			case MODE_GAME:
				delete(activeMode);
				if (!paused) 
					game = new Game(currentLevel);
				activeMode = new ApplicationModeGame();
				activeModeId = MODE_GAME;
				break;
			case MODE_MAIN_MENU:
				delete(activeMode);
				/*if(game)
					delete(game);*/
				currentLevel = 0;
				activeMode = new ApplicationModeMainMenu();
				activeModeId = MODE_MAIN_MENU;
				break;
			case MODE_OPTION_MENU:
				delete(activeMode);
				/*if (game)
					delete(game);*/
				activeMode = new ApplicationModeOptionMenu();
				activeModeId = MODE_OPTION_MENU;
				break;
			case MODE_LEVEL_MENU:
				delete(activeMode);
				/*if (game)
					delete(game);*/
				activeMode = new ApplicationModeLevelMenu();
				activeModeId = MODE_LEVEL_MENU;
				break;
			case MODE_PAUSE_MENU:
				delete(activeMode);
				if (game)
					//delete(game);
				activeMode = new ApplicationModePauseMenu();
				activeModeId = MODE_PAUSE_MENU;
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
