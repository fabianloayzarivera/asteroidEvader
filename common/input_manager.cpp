#include "stdafx.h"
#include "input_manager.h"

void InputManager::processInput() {
	// Move Player
	if (SYS_KeyPressed(SYS_KEY_UP)) {
		game->movePlayer();
	}
	// Rotate Player
	if (SYS_KeyPressed(SYS_KEY_LEFT)) {
		game->rotatePlayerLeft();
	}

	if (SYS_KeyPressed(SYS_KEY_RIGHT)) {
		game->rotatePlayerRight();
	}


}