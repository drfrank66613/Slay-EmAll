#include "Map.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

Map::Map() {
	//initialize private variables with the default values below
	_mapName = "";
	_isChanged = false;
}

Map::Map(string mapName) {
	//initialize private variables with the parameter values and some default values
	_mapName = mapName;
	_isChanged = false;
	_playerTalk = new VisitorTalk();
	_queue = new Queue(2);
	_stack = new Stack(10);
}


void Map::load(string fileMap, Player& player) {
	//Load the map
	ifstream file;
	
	file.open(fileMap);
	if (!file.is_open()) {
		cout << "Error opening file";
		exit(1);
	}
	
	string row;

	while (getline(file, row)) {
		_mapData.push_back(row);
	}

	file.close();

	//Run the map system
	char cell;
	for (size_t y = 0; y < _mapData.size(); y++) {
		for (size_t x = 0; x < _mapData[y].size(); x++) {
			cell = _mapData[y][x];

			switch (cell) {
			case '@': //player
				player.setPos(x, y);
				break;

			//Entrance		
			case 'S': //slime
				_enemies.push_back(Enemy(5, 3, 3, 5, "Slime", cell));
				_enemies.back().setPos(x, y);
				break;
			case 'B': //bat
				_enemies.push_back(Enemy(10, 3, 3, 10, "Bat", cell));
				_enemies.back().setPos(x, y);
				break;
			case 'D': //demon
				_enemies.push_back(Enemy(500, 100, 80, 480, "Demon", cell));
				_enemies.back().setPos(x, y);
				break;
			case 'T': //boss aka titan
				_enemies.push_back(Enemy(2000, 150, 150, 10000, "Titan", cell));
				_enemies.back().setPos(x, y);
				break;

			//Ruins
			case 'C': //Cyclops
				_enemies.push_back(Enemy(70, 50, 20, 100, "Cyclops", cell));
				_enemies.back().setPos(x, y);
				break;
			case 'G': //Golem
				_enemies.push_back(Enemy(200, 80, 40, 200, "Golem", cell));
				_enemies.back().setPos(x, y);
				break;

			//Forest
			case 'L': //Lizardman
				_enemies.push_back(Enemy(1, 1, 1, 1, "Lizardman", cell));//70, 50, 20, 100
				_enemies.back().setPos(x, y);
				break;
			case 'R': //Raptor
				_enemies.push_back(Enemy(1, 1, 1, 1, "Raptor", cell));//200, 80, 40, 200
				_enemies.back().setPos(x, y);
				break;
			
			}
		}
	}
}

void Map::print(Player& player){
	//print out & update the status of the player
	int index = 0;
	int arrStatVal[6] = { player.getHp(), player.getAttack(), player.getDefence(), player.getPlayerLevel(), player.getPlayerExp(), player.getExpCap()};
	string arrStatus[6] = { "Hp: ", "Attack: ", "Defence: ", "Level: ", "Current Exp: ",  "Exp Cap: "};
	system("CLS");
	cout << player;
	for (size_t i = 0; i < _mapData.size(); i++) {
		if (index < 6) {
			cout << _mapData[i] << "    " << arrStatus[i] << arrStatVal[i] << endl;
			index++;
		}
		else {
			cout << _mapData[i] << endl;
		}	
	}
	cout << endl;
}

void Map::checkPlayerMove(char keyPressed, Player& player) {
	//execute actions based on key pressed by the user
	int xPos;
	int yPos;

	player.getPos(xPos, yPos);

	switch (keyPressed) {
	case 'W': //up
	case 'w':
		executePlayerMove(xPos, yPos - 1, player);		
		break;
	case 'A': //left
	case 'a':
		executePlayerMove(xPos - 1, yPos, player);
		break;
	case 'S': //down
	case 's':
		executePlayerMove(xPos, yPos + 1, player);
		break;
	case 'D': //right
	case 'd':
		executePlayerMove(xPos + 1, yPos, player);
		break;
	case 'I': //open inventory
	case 'i':
		player.openBag();
		break;
	case 'X': //see item currently grabbed
	case 'x':
		player.seeItem();
		break;
	case '0':
		quitGame();
		break;
	default:
		cout << "Wrong key!" << endl;
		system("PAUSE");
		break;
	}
}

void Map::quitGame() {
	int keyPressed;
	bool running = true;
	
	while (running == true) {
		cout << "\nAre you sure want to leave? (Y/N) ";
		keyPressed = _getch();
		switch (keyPressed)
		{
		case 'Y':
		case 'y':
			cout << "\n===THANKS FOR PLAYING!===" << endl;
			exit(EXIT_FAILURE);
			break;
		case 'N':
		case 'n':
			cout << "\nYou continue the game..." << endl;
			running = false;
			Sleep(1000);
			break;
		default:
			cout << "Wrong key!" << endl;
			break;
		}
	}
	
}

void Map::executePlayerMove(int newXPos, int newYPos, Player& player) {
	//execute some actions while the player interacts with the objects and environment in the game
	int xPos;
	int yPos;
	srand((unsigned int)time(NULL));
	int dropChance = rand() % 2 + 1;
	player.getPos(xPos, yPos);

	char moveCell = getCell(newXPos, newYPos);

	switch (moveCell) {
	case ' ':
		player.setPos(newXPos, newYPos);
		setCell(xPos, yPos, ' ');
		setCell(newXPos, newYPos, '@');
		break;
	case '#':
		break;
	case '-':
	case '|':
		_isChanged = true;
		break;
	case '$':
		processTreasure(xPos, yPos, player);
		break;
	case '&':
		processStatue(player);
		break;
	default:
		executeBattle(newXPos, newYPos, player);
		break;
	}
	

}

void Map::processStatue(Player& player) {
	int duration = 0;
	char keyPressed;
	cout << "\nThis is a cursed statue, by using this you agree to exchange your current HP with chosen status:" << endl;
	cout << "1. Soul of Attack       3. Proceed the first soul on queue\n2. Soul of Defence      0. Cancel" << endl;
	cout << "Press the numbers (1/2/3/0) to proceed:";
	keyPressed = _getch();
	cout << endl;

	//Get the Soul of Attack
	if (keyPressed == '1') {	
		if (!_queue->isFull()) {
			cout << "You have added the Soul of Attack onto queue, proceed it to take the effect" << endl;
		}
		_queue->enqueue("Soul of Attack");
		
		system("PAUSE");
	}
	//Get the Soul of Defence
	else if (keyPressed == '2') {
		if (!_queue->isFull()) {
			cout << "You have added the Soul of Defence onto queue, proceed it to take the effect" << endl;
		}
		_queue->enqueue("Soul of Defence");
		
		system("PAUSE");
	}
	//Consume the soul based on the queue
	else if (keyPressed == '3') {
		if (_queue->peek() == "") {

		}
		else if (_queue->peek() == "Soul of Attack") {
			cout << "Your attack will increase but your current HP will be consumed" << endl;
			cout << "Processing... It takes a few moments" << endl;
			while (duration != 5) {
				duration++;
				Sleep(1000);
			}
			_queue->dequeue();
			player.setAttack(player.getAttack() + 10);
			player.setHp(player.getHp() - 20);
			cout << "Done!" << endl;
			cout << "Your attack increased by 10, your HP decreased by 20" << endl;
			system("PAUSE");
		}
		else if (_queue->peek() == "Soul of Defence") {
			cout << "Your defence will increase but your current HP will be consumed" << endl;
			cout << "Processing... It takes a few moments" << endl;
			while (duration != 5) {
				duration++;
				Sleep(1000);
			}
			_queue->dequeue();
			player.setDefence(player.getDefence() + 10);
			player.setHp(player.getHp() - 20);
			cout << "Done!" << endl;
			cout << "Your defence increased by 10, your HP decreased by 20" << endl;
			system("PAUSE");
		}
	}

	
}

void Map::setIsChanged(bool value) {
	_isChanged = value;
}

bool Map::getIsChanged() {
	return _isChanged;
}

Queue* Map::getQueue() {
	return _queue;
}

Stack* Map::getStack() {
	return _stack;
}

void Map::processTreasure(int xPos, int yPos, Player& player) {
	//player says something if finding a treasure in Ruins
	if (_mapName == "Ruins") {
		player.putItem("Ruin Sword");
		player.accept(*_playerTalk);
		cout << "The Ruin Sword" << endl;
		setCell(xPos - 1, yPos, ' ');
		system("PAUSE");
	}
	//player says something if finding a treasure in Forest
	else {
		player.putItem("Forest Sword");
		player.accept(*_playerTalk);
		cout << "The Forest Sword" << endl;
		setCell(xPos + 1, yPos, ' ');
		system("PAUSE");
	}
	delete _playerTalk;
}

void Map::showEnemiesKilled() {
	//elements in stack will be popped out
	for (int i = 0; i < 10; i++) {
		cout << _stack->pop() << endl;
	}
	
}

void Map::executeBattle(int enemyX, int enemyY, Player& player) {
	//fight the monster bumped by the player
	int enemyXPos;
	int enemyYPos;
	int playerXPos;
	int playerYPos;
	int attackChance;
	int battleResult;

	player.getPos(playerXPos, playerYPos);
	for (size_t i = 0; i < _enemies.size(); i++) {
		_enemies[i].getPos(enemyXPos, enemyYPos);

		if (enemyX == enemyXPos && enemyY == enemyYPos) {

			attackChance = player.attack();
			cout << "\nYou hit the " << _enemies[i].getName() << " with " << attackChance << " damage" << endl;
			battleResult = _enemies[i].damaged(attackChance);
			

			if (battleResult != 0) {
				setCell(enemyX, enemyY, ' ');
				print(player);
				cout << "You killed the " << _enemies[i].getName() << endl;
				_stack->push(_enemies[i].getName());
				

				player.gainExp(battleResult);
				
				player.putItem(_enemies[i].dropItem());
				cout << "You get " << _enemies[i].dropItem() << endl;
				system("PAUSE");
				return;
			}
			
			attackChance = _enemies[i].attack();
			cout << _enemies[i].getName()  << " hit you"  << " with " << attackChance << " damage" << endl;
			battleResult = player.damaged(attackChance);

			if (battleResult != 0) {
				setCell(playerXPos, playerYPos, 'X');
				print(player);
				cout << "You have been killed by the " << _enemies[i].getName() << endl;
				system("PAUSE");
				
				exit(0);
			}
			system("PAUSE");
			return;
		}
	}
}

void Map::setCell(int x, int y, char cell) {
	_mapData[y][x] = cell;
}

char Map::getCell(int x, int y) {
	char cell = _mapData[y][x];
	return cell;
}
