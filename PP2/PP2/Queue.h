#pragma once
#include <iostream>
#include <string>

using namespace std;

class Queue
{
private:
	string* _array; //store the elements of queue
	int _size; //the maximum size of the queue
	int _front; //index of the first element of queue
    int _rear; //index of the last element in queue
    int _count; //the current size of queue

public:
    Queue(int size); //constructor that takes size as parameter
    ~Queue(); //destructor

    void enqueue(string item); //to add item to the queue
    void dequeue(); //to remove the front item from the queue
    bool isEmpty(); //to check if the queue is empty
    bool isFull(); //to check if the queue is full
    int size(); //to return the size of the queue
    string peek(); //to return the front element of the queue
};

