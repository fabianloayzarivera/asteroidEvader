#pragma once
enum appModeId { MODE_IDLE, MODE_NULL, MODE_GAME, MODE_PAUSE_MENU, MODE_OPTION_MENU, MODE_WIN, MODE_GAMEOVER, MODE_MAIN_MENU, MODE_LEVEL_MENU };

class Message;
class ApplicationMode {
public:
	virtual void run() = 0;
	virtual void render() = 0;
	virtual void processInput() = 0;
	virtual void sendMessage(Message *msg) = 0;

};

struct Option
{
	int id;
	const char* name;
	appModeId modeId;
	Option(int i, const char* n, appModeId mode) { id = i, name = n; modeId = mode; }
};