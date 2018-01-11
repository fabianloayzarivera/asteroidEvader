#pragma once
#include "core.h"
class Sprite {
private:
	vec2  pos;
	float width;
	float height;
	float angle;
	GLuint gfx;
public:
	Sprite(vec2 p, float w, float h, float a, GLuint g) { pos = p; width = w; height = h; angle = a; gfx = g; }
	vec2 getPos() { return pos; }
	void setpos(const vec2 p) { pos = p; }
	float getAngle() { return angle; }
	void setAngle(const float a) { angle = a; }
	GLuint getGfx() { return gfx; }
	void setGfx(const GLuint g) { gfx = g; }
	float getWidth() { return width; }
	void setWidth(const float a) { width= a; }
	float getHeight() { return height; }
	void setHeight(const float a) { height= a; }
};