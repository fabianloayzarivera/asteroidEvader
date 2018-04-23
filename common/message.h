#pragma once

class Message {
public:
	virtual ~Message() {}
};

class UpMessage : public Message
{
public:
	bool up;
	~UpMessage() {};
};class UpHoldMessage : public Message
{
public:
	bool up;
	~UpHoldMessage() {};
};class DownMessage : public Message
{
public:
	bool down;
	~DownMessage() {};
};class ReturnMessage : public Message
{
public:
	~ReturnMessage() {};
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
	Entity* collidingEntity;
	Entity* otherEntity;
	~CollisionMessage() {};
};

class PMessage : public Message
{
public:
	~PMessage() {};
};class OMessage : public Message
{
public:
	~OMessage() {};
};class LMessage : public Message
{
public:
	~LMessage() {};
};class QMessage : public Message
{
public:
	~QMessage() {};
};class AMessage : public Message
{
public:
	~AMessage() {};
};class EMessage : public Message
{
public:
	~EMessage() {};
};class BMessage : public Message
{
public:
	~BMessage() {};
};