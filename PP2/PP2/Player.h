#pragma once
#include "Entity.h"
#include "Bag.h"
#include "DoublyLinkedList.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <vector>

using namespace std;

class Player :
    public Entity
{
private:
    Bag _bagIter = Bag(_bag); //to store the bag iterator/controller
    typedef DoublyLinkedNode<string>::Node StringNode;
    vector <string> _bag; //to store list of items in the bag
    string _playerMessage; //to store the message of the hero
    int _playerLevel; //to store the player level
    int _playerExp; //to store the player current experience
    int _expCap; //to store the player exp capacity

public:
    Player(); //default constructor
    Player(int hp, int attack, int defence, int playerLevel, int playerExp, int expCap); //constructor with parameters

    friend ostream& operator << (ostream& output, const Player& player); //friend operator used to print the hero's message to the console

    int attack(); //to return the attack damage
    int damaged(int attack); //return the damage taken
    void gainExp(int exp); //give the player experience when the enemy is killed
    string putItem(string item); //take the item dropped by enemy or found in a treasure
    void seeItem(); //see the current item chosen in the bag
    void bagNext(); //choose the next item in the bag
    void bagPrev(); //choose the previous item in the bag
    void openBag(); //print the items owned to the console if any
    void useShortcut();

    void accept(Visitor& v); //the player object accepts the visitor to add some functonalites to it

    //getters
    int getPlayerLevel() const;
    int getPlayerExp() const;
    int getExpCap() const;
    
};

