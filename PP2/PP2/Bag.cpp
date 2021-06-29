#include "Bag.h"


Bag::Bag(vector <string>& items) {
	for (int i = 0;i < items.size();i++) {
		_items[i] = items[i];
	}
	// Initialize the _index value to 0
	_index = 0;
}

Bag::Bag(const Bag& bag, int index) {
	// Store the _index value to index
	_index = index;

	// Initialize the value of bag._items to _items[i]
	for (int i = 0; i < _items.size();i++) {
		_items[i] = bag._items[i];
	}
}

const string& Bag::operator*() const {
	// Return the _items value at the current index
	return _items[_index];
}


Bag& Bag::operator++() {
	// Increment the index value by 1 & return the iterator
	_index++;
	return *this;
}

Bag Bag::operator++(int) {
	// return the iterator (old position) & Increment the index value by 1
	Bag temp = *this;
	++(*this);
	return temp;
}

Bag& Bag::operator--() {
	// Decrease the index value by 1 & return the iterator
	_index--;
	return *this;
}

Bag Bag::operator--(int) {
	// return the iterator (old position) & decrease the index value by 1
	Bag temp = *this;
	--(*this);
	return temp;
}

bool Bag::operator==(const Bag& other) const {
	// return true / false of the comparison of the two iterators
	return (_index == other._index);
}

bool Bag::operator!=(const Bag& other) const {
	return !(*this == other);
}

Bag Bag::begin() const {
	return *this;
}

Bag Bag::end() const {
	return Bag(*this, _items.size() - 1);
}

void Bag::setItems(vector <string> items) {
	_items = items;
}