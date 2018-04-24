#pragma once
#include "application_mode.h"
#include "game.h"
#include "input_manager.h"
#include "globals.h"

class ApplicationModePauseMenu :public ApplicationMode {
private:
	GLuint texWin;
	GLuint				texMark;
	float				bkgHeight;
	float				bkgWidth;
	std::vector<Option> options;
	int					optionSelected;
public:
	ApplicationModePauseMenu();
	void insertOption(const char* name, appModeId mode);
	void run() {}
	void render();
	void processInput() { inputManager->processInput(); };
	void sendMessage(Message *msg) { receiveMessage(msg); }
	void receiveMessage(Message *msg);
};