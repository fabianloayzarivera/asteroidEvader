#include "stdafx.h"
#include "application_manager.h"
#include "input_manager.h"

void InputManager::processInput() {

	//GAME

	if (SYS_KeyPressed(SYS_KEY_UP)) {

		UpMessage msg;
		msg.up = true;
		appManager->sendMessage(&msg);

	}

	if (SYS_KeyPressed(SYS_KEY_LEFT)) {

		RotateLeftMessage msg;
		msg.rotate = true;
		appManager->sendMessage(&msg);

	}

	if (SYS_KeyPressed(SYS_KEY_RIGHT)) {

		RotateRightMessage msg;
		msg.rotate = true;
		appManager->sendMessage(&msg);
		
		
	}

	if (SYS_KeyPressed(SYS_KEY_DOWN)) {
	
		DownMessage msg;
		msg.down = true;
		appManager->sendMessage(&msg);


	}

	//MENUS

	if (SYS_KeyPressed((int)VkKeyScanA('p'))) {
		PMessage msg;
		appManager->sendMessage(&msg);
	}
	if (SYS_KeyPressed((int)VkKeyScanA('o'))) {
		OMessage msg;
		appManager->sendMessage(&msg);
	}
	if (SYS_KeyPressed((int)VkKeyScanA('l'))) {
		LMessage msg;
		appManager->sendMessage(&msg);
	}
	if (SYS_KeyPressed((int)VkKeyScanA('q'))) {
		QMessage msg;
		appManager->sendMessage(&msg);
	}
	if (SYS_KeyPressed((int)VkKeyScanA('a'))) {
		AMessage msg;
		appManager->sendMessage(&msg);
	}
	if (SYS_KeyPressed((int)VkKeyScanA('e'))) {
		EMessage msg;
		appManager->sendMessage(&msg);
	}
	if (SYS_KeyPressed((int)VkKeyScanA('b'))) {
		BMessage msg;
		appManager->sendMessage(&msg);
	}
	

}