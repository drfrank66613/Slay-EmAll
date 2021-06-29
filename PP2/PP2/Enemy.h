#pragma once
#include "Entity.h"
#include <string>

using namespace std;

class Enemy :
    public Entity
{
private:
    int _expGiven; //experience given when the enemy dies
    string _possibleDrops[3] = {"Golden Sword", "Golden Armor", "Potion"}; //an item is dropped when the enemy dies
    string _name; //name of the enemy
    char _symbol; //symbol to represent the enemy

public:
    Enemy(); //default constructor
    Enemy(int hp, int attack, int defence, int expGiven, string name, char symbol); //constructor with paramaters

    int damaged(int attack); //damage taken by the enemy
    string dropItem(); //the enemy drops an item

    //getters
    string getName() const;
};

