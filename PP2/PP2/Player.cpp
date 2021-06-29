#include "Player.h"

Player::Player() {
	//initialize private variables with the default values below
	_playerExp = 0;
	_playerLevel = 0;
	_expCap = 0;

}

Player::Player(int hp, int attack, int defence, int playerLevel, int playerExp, int expCap) : Entity(hp,attack,defence) {
	//initialize private variables with the parameter values and a default value
	_playerLevel = playerLevel;
	_playerExp = playerExp;
	_expCap = expCap;
	_playerMessage = "I will slay them all and become much stronger";

}

ostream& operator << (ostream& output, const Player& player) {
	output << player._playerMessage << endl;
	return output;
}

int Player::attack() {
	//return the damage that will be given based on the number generated by the RNG 
	srand((unsigned int)time(NULL));
	return rand() % _attack + 0;

}

void Player::accept(Visitor& v) {
	v.Visit(*this);
}

int Player::damaged(int attack) {
	attack -= _defence;
	if (attack > 0) {
		_hp -= attack;

		if (_hp <= 0) {
			return 1;
		}
	}
	return 0;
}

void Player::gainExp(int exp) {
	//by killing monster, player can gain exp and level up
	_playerExp += exp;

	while (_playerExp > _expCap) {
		_playerExp -= _expCap;
		_attack += 10;
		_defence += 5;
		_hp += 15;
		_playerLevel++;
		_expCap += 50;
		cout << "You are getting stronger!" << endl;
		system("PAUSE");
	}
}

string Player::putItem(string item) {
	//put item to the inventory
	_bag.push_back(item);
	_bagIter.setItems(_bag);
	return item;
	
}

void Player::seeItem() {
	//player can see the item grabbed currently as well as the previous and next items
	if (_bag.size() > 0) {
		cout << "\nYou grab " << *_bagIter << endl;
		cout << "Press z to see the previous item" << endl;
		cout << "Press c to see the next item" << endl;
		bool isTrue = true;
		while (isTrue) {
			char input = _getch();
			switch (input) {
			case 'z':
			case 'Z':
				bagPrev();
				break;
			case 'c':
			case 'C':
				bagNext();
				break;
			default:
				isTrue = false;
				break;
			}
		}
	}
	else {
		cout << "\nThere is no item in your inventory" << endl;
	}
	system("PAUSE");
}


void Player::bagNext() {
	if (_bagIter != _bagIter.end()) {
		_bagIter++;
		cout << "\nYou grab " << *_bagIter << endl;
		cout << "Press z to see the previous item" << endl;
		cout << "Press c to see the next item" << endl;
	}
	else {
		cout << "\nThere is no more item to search!" << endl;
	}
	system("PAUSE");
}

void Player::bagPrev() {
	if (_bagIter != _bagIter.begin()) {
		_bagIter--;
		cout << "\nYou grab " << *_bagIter << endl;
		cout << "Press z to see the previous item" << endl;
		cout << "Press c to see the next item" << endl;
	}
	else {
		cout << "\nThis is your first item, please go next to search for more item!" << endl;
	}
	system("PAUSE");
}

int Player::getPlayerLevel() const {
	return _playerLevel;
}

int Player::getPlayerExp() const {
	return _playerExp;
}

int Player::getExpCap() const {
	return _expCap;
}

void Player::openBag() {
	//show all the items in inventory
	cout << "\nList of items in your inventory: " << endl;
	if (_bag.size() == 0) {
		cout << "No item" << endl;
	}
	else {
		for (size_t i = 0; i < _bag.size(); i++) {
			cout << _bag[i] << endl;
		}
	}
	system("PAUSE");
}

void Player::useShortcut() {
	for (size_t i = 0; i < _bag.size(); i++) {
		if (_bag[i] == "Golden Sword" || "Golden Armor" || "Potion") {
			
		}
	}
}