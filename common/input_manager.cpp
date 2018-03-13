#include "stdafx.h"
#include "input_manager.h"

void InputManager::processInput() {
	// Move Player
	if (SYS_KeyPressed(SYS_KEY_UP)) {
		//playerPtr->movePlayer();
		MoveMessage msg;
		msg.move = true;
		game->sendMessage(&msg);

	}
	// Rotate Player
	if (SYS_KeyPressed(SYS_KEY_LEFT)) {
		//playerPtr->rotatePlayerLeft();
		RotateLeftMessage msg;
		msg.rotate = true;
		game->sendMessage(&msg);

	}

	if (SYS_KeyPressed(SYS_KEY_RIGHT)) {
		//playerPtr->rotatePlayerRight();
		RotateRightMessage msg;
		msg.rotate = true;
		game->sendMessage(&msg);
	}


}