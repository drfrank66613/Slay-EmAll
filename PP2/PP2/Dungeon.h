#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class Dungeon
{
private:
	T* _room; //Store the value of the room

	//Pointer to left, right and back of the tree
	Dungeon<T>* _left;
	Dungeon<T>* _right;
	Dungeon<T>* _back;

	//Constructor used to set the value of the variables to Null
	Dungeon() : _room((T*)0) {
		_left = &NIL;
		_right = &NIL;
		_back = &NIL;
	}

public:
	static Dungeon<T> NIL; //Sentinel which represents nothing

	Dungeon(T* room) : _room(room) {
		_left = &NIL;
		_right = &NIL;
		_back = &NIL;
	}

	//Destructor
	~Dungeon() {
		if (_left != &NIL) {
			delete _left;
		}
		if (_right != &NIL) {
			delete _right;
		}
		if (_back != &NIL) {
			delete _back;
		}
	}

	//To check whether the current tree node is empty
	bool isEmpty() const {
		return this == &NIL;
	}

	//Return the value of the room in the current tree node
	T& room() {
		if (isEmpty()) {
			throw domain_error("Empty Room\n");
		}
		else {
			return *_room;
		}
	}

	//Return the pointer of the left tree node
	Dungeon* left() {
		if (_left == &NIL) {
			cout << "No room on the left\n";
			return this;
		}
		return _left;
	}

	//Return the pointer of the right tree node
	Dungeon* right() {
		if (_right == &NIL) {
			cout << "No room on the right\n";
			return this;
		}
		return _right;
	}

	//Return the pointer of the back tree node
	Dungeon* back() {
		if (_back == &NIL) {
			cout << "You are currently at the entrance\n";
			return this;
		}
		return _back;
	}


	//Attach room to the left of current tree node
	void attachLeft(Dungeon<T>* room) {
		if (isEmpty()) {
			throw domain_error("Empty Room");
		}
		if (_left != &NIL) {
			throw domain_error("Non-empty sub Room");
		}
		_left = room;
	}

	//Attach room to the right of current tree node
	void attachRight(Dungeon<T>* room) {
		if (isEmpty()) {
			throw domain_error("Empty Room");
		}
		if (_right != &NIL) {
			throw domain_error("Non-empty sub Room");
		}
		_right = room;
	}

	//Attach room to the back of current tree node
	void attachBack(Dungeon<T>* room) {
		if (isEmpty()) {
			throw domain_error("Empty Room");
		}
		_back = room;
	}

	//Detach room at the left of current tree node
	Dungeon* detachLeft() {
		if (isEmpty()) {
			throw domain_error("Empty Room");
		}
		Dungeon<T>& Result = *_left;
		_left = &NIL;
		return &Result;
	}

	//Detach room at the right of current tree node
	Dungeon* detachRight() {
		if (isEmpty()) {
			throw domain_error("Empty Room");
		}
		Dungeon<T>& Result = *_right;
		_right = &NIL;
		return &Result;
	}

	//Detach room at the back of current tree node
	Dungeon* detachBack() {
		if (isEmpty()) {
			throw domain_error("Empty Room");
		}
		Dungeon<T>& Result = *_back;
		_back = &NIL;
		return &Result;
	}
};

template <class T>
Dungeon<T> Dungeon<T>::NIL;

