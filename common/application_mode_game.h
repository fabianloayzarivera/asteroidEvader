#pragma once
#include "application_mode.h"
#include "game.h"
#include "globals.h"

class ApplicationModeGame :public ApplicationMode {
public:

	void run() { game->run(); }
	void render() { game->render(); }
	void processInput() { game->processInput(); }

};