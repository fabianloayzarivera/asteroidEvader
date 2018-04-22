#pragma once
#include "application_mode.h"
#include "game.h"
#include "globals.h"

class ApplicationModeGameOver :public ApplicationMode {
private:
	GLuint texGameOver;
	float bkgHeight;
	float bkgWidth;
public:
	ApplicationModeGameOver();
	void run() {}
	void render();
	void processInput();
	void sendMessage(Message *msg) {}

};