#include "stdafx.h"
#include "application_manager.h"
#include "input_manager.h"

InputManager::InputManager() 
{
	oldKeys["Down"] = false;
	oldKeys["Up"] = false;
}

void InputManager::processInput() {

	//GAME

	if (SYS_KeyPressed(SYS_KEY_UP)) 
		newKeys["Up"] = true;
	else
		newKeys["Up"] = false;


	if (SYS_KeyPressed(SYS_KEY_DOWN))
		newKeys["Down"] = true;
	else
		newKeys["Down"] = false;

	if (SYS_KeyPressed(VK_RETURN))
		newKeys["Return"] = true;
	else
		newKeys["Return"] = false;

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

	
	if (checkReleased("Down")) {
		DownMessage msg;
		msg.down = true;
		appManager->sendMessage(&msg);
	}

	if (checkReleased("Up"))
	{
		UpMessage msg;
		msg.up = true;
		appManager->sendMessage(&msg);
	}
	else if (checkHold("Up")) 
	{
		UpHoldMessage msg;
		msg.up = true;
		appManager->sendMessage(&msg);
	}

	if (checkReleased("Return")) {
		ReturnMessage msg;
		appManager->sendMessage(&msg);
	}

	oldKeys["Down"] = newKeys["Down"];
	oldKeys["Up"] = newKeys["Up"];
	oldKeys["Return"] = newKeys["Return"];



	//MENUS
	if (SYS_KeyPressed((int)VkKeyScanA('o'))) {
		OMessage msg;
		appManager->sendMessage(&msg);
	}
	if (SYS_KeyPressed((int)VkKeyScanA('e'))) {
		EMessage msg;
		appManager->sendMessage(&msg);
	}

	/*if (SYS_KeyPressed((int)VkKeyScanA('p'))) {
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
	}*/
	

}

bool InputManager::checkReleased(const char* key) 
{
	return oldKeys[key] && !newKeys[key];
}

bool InputManager::checkHold(const char* key)
{
	return oldKeys[key] && newKeys[key];
}