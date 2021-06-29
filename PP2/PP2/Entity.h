#pragma once
#include <stdio.h> 
#include <stdlib.h> 
#include<time.h>
#include "Visitor.h"

class Entity
{
protected:
	int _hp; //health point of the entity object
	int _attack; //The entity's attack
	int _defence; //The entity's defence
	int _xPos; //x position of the entity
	int _yPos; //y position of the entity

public:
	
	Entity(); //default constructor
	Entity(int hp, int attack, int defence); //constructor with parameters

	virtual int attack(); //the entity attacks and return the attack damage
	virtual int damaged(int attack)=0; //damage taken by the entity
	virtual void accept(Visitor& v);

	//setters
	void setPos(int xPos, int yPos);
	void setHp(int value);
	void setAttack(int value);
	void setDefence(int value);

	//getters
	void getPos(int& xPos, int& yPos);
	int getHp() const;
	int getAttack() const;
	int getDefence() const;
};

