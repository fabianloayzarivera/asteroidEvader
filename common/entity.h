#pragma once
#include "core.h"
#include <vector>
#include "sprite.h"
enum entityType {ENTITY_PLAYER, ENTITY_ASTEROID, ENTITY_STATION};

class Component;
class Message;


class Entity {
private:
	vec2 pos;
	GLuint gfx;
	float radius;
	float angle;
	entityType type;
	Sprite* sprite;
	std::vector<Component*> m_Components;
public:
	vec2					getPos    () const         { return pos;    }
	void					setPos    (const vec2 p)   { pos = p;       }
	float					getRadius () const         { return radius; }
	void					setRadius (const float r)  { radius = r;    }
	GLuint					getGfx    () const         { return gfx;    }
	void					setGfx    (const GLuint f) { gfx = f;       }
	entityType				getType	  ()			   { return type; }
	void					setType	  (entityType t)   { type = t; }
	float					getAngle  ()			   { return angle; }
	void					setAngle  (const float a)  { angle = a; }
	Sprite*					getSprite() { return sprite; }
	void					setSprite(Sprite* s) { sprite = s; }
	virtual void update() = 0;
	void					addComponent(Component* c) { m_Components.push_back(c); }
	std::vector<Component*> getComponents() { return m_Components; }
	void					receiveMessage(Message *msg);
	virtual void			onCollision(vec2 pos, Entity *otherEntity) = 0;
	template<class T> T*    FindComponent();
	virtual bool			isCollisionable() = 0;
};

