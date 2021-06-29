#pragma once
#include <string>
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "Map.h"
#include "Dungeon.h"
#include "Visitor.h"

using namespace std;

class GameSystem
{
private:
	Map* _map; //map1 or room1 (Entrance)
	Map* _map2; //map2 or room2 (Ruins)
	Map* _map3; //map3 or room3 (Desert)

	//Tree nodes which represent the respective rooms
	Dungeon<Map>* _currentMap;
	Dungeon<Map>* _entrance;
	Dungeon<Map>* _ruins;
	Dungeon<Map>* _forest;
	Player _player; //the player in the game
	

public:
	GameSystem(); //constructor

	void run(); //run the game
	void movePlayer(); //a system to move the player
};

