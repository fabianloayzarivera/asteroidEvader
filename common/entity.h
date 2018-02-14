#pragma once
#include "core.h"
#include <vector>
#include "sprite.h"

enum entityType {ENTITY_PLAYER, ENTITY_ASTEROID, ENTITY_STATION};

class Component;

class Entity {
private:
	vec2 pos;
	GLuint gfx;
	float radius;
	float angle;
	entityType type;
	Sprite* sprite;
	std::vector<Component*> components;
	
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
	Sprite*		getSprite() { return sprite; }
	void		setSprite(Sprite* s) { sprite = s; }
	virtual void update();
	void		addComponent(Component* c) { components.push_back(c); }
	//void		receiveMessage(Message *msg);
};