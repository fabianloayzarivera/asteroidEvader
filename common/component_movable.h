#pragma once
#include "component.h"
#define PLAYER_MOVEMENT_SPEED_DEFAULT 8.f
#define PLAYER_ROTATION_SPEED_DEFAULT 0.085f

class ComponentMovable: public Component {
private:
	vec2   pos;
	vec2   vel;
	float  angle;
public:
	void		move();
	void		rotateLeft();
	void		rotateRight();
	vec2		getPos() const { return pos; }
	void		setPos(const vec2 p) { pos = p; }
	float		getAngle() { return angle; }
	void		setAngle(const float a) { angle = a; }
	const vec2  getVel() { return vel; }
	void		setVel(const vec2 v) { vel = v; }
};