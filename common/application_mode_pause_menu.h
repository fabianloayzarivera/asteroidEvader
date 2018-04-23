#pragma once
#include "application_mode.h"
#include "game.h"
#include "input_manager.h"
#include "globals.h"

class ApplicationModePauseMenu :public ApplicationMode {
private:
	GLuint texWin;
	float bkgHeight;
	float bkgWidth;
public:
	ApplicationModePauseMenu();
	void run() {}
	void render();
	void processInput() { inputManager->processInput(); };
	void sendMessage(Message *msg) { receiveMessage(msg); }
	void receiveMessage(Message *msg);
};