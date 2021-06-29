#pragma once
#include <iostream>

using namespace std;

// Class for stack
class Stack
{
    string* _array; //store the elements of queue
    int _size; //the maximum size of the stack
    int _top; //store the index of element in the queue
    
public:
    Stack(int size); //constructor that takes size as parameter
    ~Stack(); //destructor

    void push(string value); //to add item to the stack
    string pop(); //to remove top element from the stack
    bool isEmpty(); //to check if the stack is empty
    bool isFull(); //to check if the stack is full
    int size(); //to return the size of the queue
    string peek(); //to return the top element of the stack
  
};

