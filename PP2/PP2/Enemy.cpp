#include "Enemy.h"

Enemy::Enemy() {
    //initialize private variables with the default values below
    _expGiven = 0;
    _name = "No Name";
    _symbol = '?';
}

Enemy::Enemy(int hp, int attack, int defence, int expGiven, string name, char symbol) : Entity(hp, attack, defence) {
    //initialize private variables with the parameter values
    _expGiven = expGiven;
    _name = name;
    _symbol = symbol;
}

int Enemy::damaged(int attack) {
    attack -= _defence;
    if (attack > 0) {
        _hp -= attack;

        if (_hp <= 0) {
            return _expGiven;
        }
    }
    return 0;
}

string Enemy::dropItem() {
    //return the item that has been generated from the RNG (Random Number Generator)
    srand((unsigned int)time(NULL));
    int dropChance = rand() % 10 + 1;
    switch (dropChance)
    {
    case 1:
        return _possibleDrops[0];
        break;
    case 2:
        return _possibleDrops[1];
        break;
    default:
        return _possibleDrops[2];
        break;
    }
}


string Enemy::getName() const {
    return _name;
}