#include "GameSystem.h"
#include <cstdlib>
#include <conio.h>

GameSystem::GameSystem() {
	_player = Player(100, 10, 5, 1, 0, 10); //initialize player object
	
	//initialize Maps or Rooms to the game
	_map = new Map("Entrance");
	_map2 = new Map("Ruins");
	_map3 = new Map("Forest");

	//initialize Dungeon that controls each room
	_entrance = new Dungeon<Map>(_map);
	_ruins = new Dungeon<Map>(_map2);
	_forest = new Dungeon<Map>(_map3);
	
	//set up the dungeon with rooms
	_entrance->attachLeft(_ruins);
	_entrance->attachRight(_forest);

	_ruins->attachBack(_entrance);

	_forest->attachBack(_entrance);

	_currentMap = _entrance;

	_currentMap->room().load("Map.txt", _player);
	_currentMap->room().print(_player);
		
}

void GameSystem::run() {
	bool gameRunning = true;
	bool ruinsVisited = false;
	bool forestVisited = false;
	
	//keep running the game until player wins or exit the game
	while (gameRunning == true) {
		_currentMap->room().print(_player);
		movePlayer();
		
		//change the room if player goes out of entrance
		if (_currentMap == _entrance) {
			while (_map->getIsChanged() == true) {
				char keyPressed;
				cout << "\nWhere you want to go? (Left/Right)" << endl;
				cout << "Press 'A' to go left or 'D' to go right or 'S' to cancel: ";
				keyPressed = _getch();

				switch (keyPressed) {
					//player goes to ruins
				case 'A':
				case 'a':
					_currentMap = _currentMap->left();		
					_currentMap->room().load("Map2.txt", _player);
					_map->setIsChanged(false);			
					break;
					//player goes to forest
				case 'D':
				case 'd':				
					_currentMap = _currentMap->right();
					_currentMap->room().load("Map3.txt", _player);				
					_map->setIsChanged(false);
					break;
				case 'S':
				case 's':
					cout << "\nYou refused to go" << endl;
					system("PAUSE");
					_map->setIsChanged(false);
					break;
				default:
					cout << "Wrong Key!" << endl;
					system("PAUSE");
					_currentMap->room().print(_player);				
					break;
				}
			}
		}
		//goes back if player goes out of the forest of ruins
		else {
			while (_map2->getIsChanged() || _map3->getIsChanged() == true) {
				char keyPressed;
				cout << "\nDo you want to go back? (Yes/No)" << endl;
				cout << "Press 'Y' to go back or 'N' to stay: ";
				keyPressed = _getch();

				switch (keyPressed) {
				case 'Y':
				case 'y':
					
					_currentMap = _currentMap->back();
					if (_currentMap->room().getCell(19, 16) == '@') {
						_player.setPos(19, 16);
					}
					else {
						_player.setPos(20, 16);
					}
									
					_map2->setIsChanged(false);
					_map3->setIsChanged(false);
					break;
				case 'N':
				case 'n':
					cout << "\nYou refused to go back" << endl;
					system("PAUSE");
					_map2->setIsChanged(false);
					_map3->setIsChanged(false);
					break;
				default:
					cout << "Wrong Key!" << endl;
					system("PAUSE");
					_currentMap->room().print(_player);				
					break;
				}
			}
		}
		
	}

	//delete the memory used in the heap
	delete _map;
	delete _map2;
	delete _map3;
	delete _entrance;
	delete _ruins;
	delete _forest;
	delete _map->getQueue();
	delete _map2->getQueue();
	delete _map3->getQueue();
	delete _map->getStack();

}

void GameSystem::movePlayer() {
	char keyPressed;
	cout << "Press 0 to quit the game" << endl;
	cout << "Press 9 to save the game\n" << endl;
	cout << "Press x to see the current item selected" << endl;
	cout << "Press i to open your inventory\n" << endl;
	cout << "Press the move keys (w/a/s/d) to move: ";
	keyPressed = _getch();

	_currentMap->room().checkPlayerMove(keyPressed, _player);
	if (_map->getStack()->size() == 10) {
		cout << "\nThe list of enemies you have killed so far (Ordered from newest to oldest):" << endl;
		_map->showEnemiesKilled();
		cout << "\nThe list will be renewed" << endl;
		system("PAUSE");
	}
		
	
}