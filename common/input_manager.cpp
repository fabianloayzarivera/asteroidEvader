#include "stdafx.h"
#include "input_manager.h"

void InputManager::processInput() {
	// Move Player
	if (SYS_KeyPressed(SYS_KEY_UP)) {
		playerPtr->movePlayer();
	}
	// Rotate Player
	if (SYS_KeyPressed(SYS_KEY_LEFT)) {
		playerPtr->rotatePlayerLeft();
	}

	if (SYS_KeyPressed(SYS_KEY_RIGHT)) {
		playerPtr->rotatePlayerRight();
	}


}