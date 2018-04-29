#pragma once
#include "application_mode.h"
#include "game.h"
#include "input_manager.h"
#include "globals.h"

class ApplicationModeLevelMenu :public ApplicationMode {
private:
	GLuint				texWin;
	GLuint				texMark;
	float				bkgHeight;
	float				bkgWidth;
	std::vector<Option> options;
	int					optionSelected;
public:
	ApplicationModeLevelMenu();
	void insertOption(const char* name, appModeId mode);
	void run() {}
	void render();
	void processInput() { inputManager->processInput(); };
	void sendMessage(Message *msg) { receiveMessage(msg); }
	void receiveMessage(Message *msg);
	~ApplicationModeLevelMenu() {
		CORE_UnloadPNG(texWin);
		CORE_UnloadPNG(texMark);
	}
};