#pragma once
class ApplicationMode {
public:
	virtual void run() = 0;
	virtual void render() = 0;
	virtual void processInput() = 0;

};