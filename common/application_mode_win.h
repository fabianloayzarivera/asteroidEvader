#pragma once
#include "application_mode.h"
#include "game.h"
#include "globals.h"
#include "input_manager.h"

class ApplicationModeWin :public ApplicationMode {
private:
	GLuint texWin;
	float bkgHeight;
	float bkgWidth;
public:
	ApplicationModeWin();
	void run() {}
	void render();
	void processInput() { inputManager->processInput(); }
	void sendMessage(Message *msg) { receiveMessage(msg); }
	void receiveMessage(Message *msg);
	~ApplicationModeWin() {
		CORE_UnloadPNG(texWin);
	}
};