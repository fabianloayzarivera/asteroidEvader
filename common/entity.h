#pragma once
#include "core.h"
#include <vector>

enum entityType {ENTITY_PLAYER, ENTITY_ASTEROID, ENTITY_STATION};

class Entity {
private:
	vec2 pos;
	GLuint gfx;
	float radius;
	float angle;
	entityType type;
public:
	vec2		getPos    () const         { return pos;    }
	void		setPos    (const vec2 p)   { pos = p;       }
	float		getRadius () const         { return radius; }
	void		setRadius (const float r)  { radius = r;    }
	GLuint		getGfx    () const         { return gfx;    }
	void		setGfx    (const GLuint f) { gfx = f;       }
	entityType	getType	  ()			   { return type; }
	void		setType	  (entityType t)   { type = t; }
	float		getAngle  ()			   { return angle; }
	void		setAngle  (const float a)  { angle = a; }
	virtual void update() = 0;
};