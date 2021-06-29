#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;

class Map
{
private:
	Visitor* _playerTalk; //to store visitor function
	Queue* _queue; //to store the queue of the soul statue
	Stack* _stack; //to store the stack of the enemies killed list
	string _mapName; //to store the map's name
	vector <Enemy> _enemies; //to store list of enemies
	vector <string> _mapData; //to store the map data taken from txt file per line
	bool _isChanged; //to store bool value to indicate if room is changed
public:
	Map(); //default constructor
	Map(string mapName); //constructor that stores the map's name

	void load(string fileMap, Player& player); //load the map which consists of the player and enemies to the game
	void print(Player& player); //print the map loaded
	void checkPlayerMove(char keyPressed, Player& player); //to check if player can move or not
	void showEnemiesKilled(); //show 10 enemies that has been killed

	//setters
	void setCell(int x, int y, char cell);
	void setIsChanged(bool value);

	//getters
	char getCell(int x, int y);
	bool getIsChanged();
	Queue* getQueue();
	Stack* getStack();
	
private:
	void executePlayerMove(int newXPos, int newYPos, Player& player); //to execute player move if some conditions are valid
	void executeBattle(int enemyX, int enemyY, Player& player); //to execute the battle if the player meets the enemy

	void processTreasure(int xPos, int yPos, Player& player); //to execute some actions if a treasure has been found
	void processStatue(Player& player); //to execute some actions if the soul statue is being used
	void quitGame(); //to quit the game



};

