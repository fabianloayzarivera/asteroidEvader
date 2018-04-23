#pragma once
#include "sys.h"
#include "game.h"
#include "globals.h"
#include <map>

class InputManager {
private:
	//Player *playerPtr;
	std::map<string, bool> oldKeys;
	std::map<string, bool> newKeys;
public:
	InputManager();
	void processInput();
	bool checkReleased(const char* key);
	bool checkHold(const char* key);
	//void setPlayerPtr(Player* p) { playerPtr = p; }
};