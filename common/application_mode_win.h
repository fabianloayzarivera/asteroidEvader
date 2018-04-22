#pragma once
#include "application_mode.h"
#include "game.h"
#include "globals.h"

class ApplicationModeWin :public ApplicationMode {
private:
	GLuint texWin;
	float bkgHeight;
	float bkgWidth;
public:
	ApplicationModeWin();
	void run() {}
	void render();
	void processInput();
	void sendMessage(Message *msg) {}
};