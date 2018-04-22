#pragma once
class Message;
class ApplicationMode {
public:
	virtual void run() = 0;
	virtual void render() = 0;
	virtual void processInput() = 0;
	virtual void sendMessage(Message *msg) = 0;

};