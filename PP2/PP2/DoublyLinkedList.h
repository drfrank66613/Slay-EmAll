#pragma once

template<class DataType>
class DoublyLinkedNode
{
public:
	//reduce the verbose name to Node
	typedef DoublyLinkedNode<DataType> Node;
private:
	DataType _value;
	Node* _next;
	Node* _previous;
	DoublyLinkedNode()
	{
		_value = DataType();
		_next = &NIL;
		_previous = &NIL;
	}
public:
	//Sentinel node that refers to nothing (like nullptr)
	static Node NIL;
	//Constructor
	DoublyLinkedNode( const DataType& value ) {
		_value = value;
		//point to nothing at first
		_next = &NIL;
		_previous = &NIL;
	}
	//Methods
	void prepend( Node& node ) {
		//node<->this
		//Let node point to this first, node->this
		node._next = this;

		//if our previous is not NIL we have to move things
		if(_previous != &NIL){
			//previous<->this, becomes previous<->node<->this
			//node now points the previous, previous<-aNode
			node._previous = _previous;
			//now the previous->node
			_previous->_next = &node;
		}
		//now set _previous as node, node<-this
		_previous = &node;
	}

	void append( Node& node ) {
		//this<->node
		node._previous = this; //this<-node

		//if there is already a _next
		if(_next != &NIL){
			//this<->next, change to this<->node<->next
			//node now points to the next, node->next
			node._next = _next;
			_next->_previous = &node; //now next points backwards to node, node<-next
		}

		_next = &node; //this->node;
	}
	void remove() {
		//previous<->this<->next, to previous<->next with this pointing to NIL in front and behind
		
		//First check if _next/_previous are NIL
		//If so make the previous->NIL or next->NIL
		if(_next == &NIL){ 
			//If no next but previous exists, then from previous<->this<->NIL to NIL<->this<->NIL
			_previous->_next = &NIL;
		}
		else if(_previous == &NIL){
			//If no previous but next exists, then from NIL<->this<->next to NIL<->this<->NIL
			_next->_previous = &NIL;
		}
		else {
			//If both previous and next exist, previous<->next
			_previous->_next = _next; // previous->next
			_next->_previous = _previous; // previous<-next
		}

		//delete this; optionable
	}

	//getters
	const DataType& getValue() const { return _value; }
	//returns the address of _next/_previous
	const Node& getNext() const { return *_next; }
	const Node& getPrevious() const { return *_previous; }
};

//"Implements" the NIL node where it's nothing
template<class DataType>
DoublyLinkedNode<DataType> DoublyLinkedNode<DataType>:: NIL;
