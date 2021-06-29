#pragma once

//Forward declaration for Entity & Player
class Entity;
class Player;

//The interface of Visitor
class Visitor
{
public:
	virtual void Visit(Entity& E);
	virtual void Visit(Player& P);
};

//To make the object visited by Visitor to be able to say something
class VisitorTalk : public Visitor
{

public:
	VisitorTalk();

	virtual void Visit(Entity& E);
	virtual void Visit(Player& P);
};