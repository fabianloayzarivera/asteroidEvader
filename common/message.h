#pragma once

class Message {
public:
	virtual ~Message() {}
};

class MoveMessage : public Message
{
public:
	bool move;
	~MoveMessage() {};
};class RotateLeftMessage : public Message
{
public:
	bool rotate;
	~RotateLeftMessage() {};
};

class RotateRightMessage : public Message
{
public:
	bool rotate;
	~RotateRightMessage() {};
};

class CollisionMessage : public Message
{
public:
	vec2 posCollision;
	Entity* otherEntity;
	~CollisionMessage() {};
};