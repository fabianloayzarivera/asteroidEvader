#pragma once
#include "entity.h"

class Player :public Entity{
private:
	//vec2   pos;
	vec2   vel;
	float  angle;
	//float  radius;
public:
	/*const vec2 getPos() { return pos; }
	void setPos(const vec2 p) { pos = p; }*/
	const vec2 getVel() { return vel; }
	void setVel(const vec2 v) { vel = v; }
	/*const float getRadius() { return radius; }
	void setRadius(const float r) { radius = r; }*/
	const float getAngle() { return angle; }
	void setAngle(const float a) { angle = a; }
};