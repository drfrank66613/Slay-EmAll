#include "Stack.h"

Stack::Stack(int size)
{
    //initialize private variables with the parameter values and a default value
    _array = new string[size];
    _size = size;
    _top = -1;
}


Stack::~Stack()
{
    //to clean memory allocated to the stack
    delete[] _array;
}


void Stack::push(string value)
{
    //if full then print the message else add item to the stack
    if (isFull())
    {
        cout << "The stack is full!";
    }
    else {
        _array[++_top] = value;
    }
}


string Stack::pop()
{
    //if empty then print & return the messages else remove top item from the stack
    if (isEmpty())
    {
        cout << "There is no item in stack";
        return "No enemy killed";
    }
    else {
        return _array[_top--];
    }

    
}


string Stack::peek()
{
    //if not empty then return the top element else return the message
    if (!isEmpty()) {
        return _array[_top];
    }
    else {
        return "No item in the stack";
    }
        
}

//Return the size of the stack
int Stack::size()
{
    return _top + 1;
}

//Check if the stack is empty
bool Stack::isEmpty()
{
    return _top == -1;
}

//Check if the stack is full
bool Stack::isFull()
{
    return _top == _size - 1;
}