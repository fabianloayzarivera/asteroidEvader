#pragma once
#include "core.h"

class Entity {
private:
	vec2 pos;
	GLuint gfx;
	float radius;
public:
	const vec2 getPos() { return pos; }
	void setPos(const vec2 p) { pos = p; }
	const float getRadius() { return radius; }
	void setRadius(const float r) { radius = r; }
	const GLuint getGfx() { return gfx; }
	void setGfx(const GLuint f) { gfx = f; }
};