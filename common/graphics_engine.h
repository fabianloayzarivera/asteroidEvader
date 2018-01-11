#pragma once
#include "sys.h"
#include "game.h"
#include "globals.h"

class GraphicsEngine {
private:
	vector<Sprite*> sprites;
	float bkgWidth;
	float bkgHeight;
	GLuint texBkg;
public:
	void pushSprite(Sprite* s) { sprites.push_back(s); }
	vector<Sprite*> getSprites() { return sprites; }
	float getBkgWidth() { return bkgWidth; }
	void setBkgWidth(float w) { bkgWidth = w; }
	float getBkgHeight() { return bkgHeight; }
	void setBkgHeight(float h) { bkgHeight = h; }
	GLuint getTexBkg() { return texBkg; }
	void setTexBkg(GLuint t) { texBkg = t; }
	void render();
};