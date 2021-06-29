#pragma once
#include <string>
#include <vector>

using namespace std;

class Bag
{
private:
	vector <string> _items; //list of items
	int _index; //to store the index postion
public:
	/*Constructor*/

	Bag(vector <string>& items);
	//Used by the auxiliary to create a copy but at a specific position
	Bag(const Bag& bag, int index);

	//Dereference operator, returns current value at the current position
	const string& operator*() const;

	/*Movement methods*/
	//prefix ++i, increment and return the iterator
	Bag& operator++();
	//postfix i++, return the iterator (old position) then increment
	Bag operator++(int);

	Bag& operator--(); //prefix --i, decrease and return the iterator
	Bag operator--(int); //postfix i++, return the iterator (old position) then decrease

	//Equivalence methods to compare two iterators, used together with begin/end e.g iter != iter.end()
	bool operator==(const Bag& other) const;
	bool operator!=(const Bag& other) const;

	//Auxiliary methods, to return a copy of the iterator but now at the beginning and end positions
	Bag begin() const;
	Bag end() const;

	void setItems(vector <string> items);

};

