#pragma once
#include "core.h"
class Sprite {
private:
	vec2  pos;
	float angle;
	GLuint gfx;
public:
	Sprite(GLuint g) { gfx = g; }
	vec2 getPos() { return pos; }
	void setpos(const vec2 p) { pos = p; }
	float getAngle() { return angle; }
	void setAngle(const float a) { angle = a; }
	GLuint getGfx() { return gfx; }
	void setGfx(const GLuint g) { gfx = g; }
};