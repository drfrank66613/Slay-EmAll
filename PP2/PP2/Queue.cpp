#include "Queue.h"

Queue::Queue(int size)
{
    //initialize private variables with the parameter values and a default value
    _array = new string[size];
    _size = size;
    _front = 0;
    _rear = -1;
    _count = 0;
}


Queue::~Queue()
{
    //to clean memory allocated to the queue
    delete[] _array;
}


void Queue::enqueue(string item)
{
    //if full print the message else add item to the queue
    if (isFull())
    {
        cout << "The queue is full! Please process one of the souls\n";
    }
    else {
        _rear = (_rear + 1) % _size;
        _array[_rear] = item;
        _count++;      
    }
}


void Queue::dequeue()
{
    //if empty print the message else remove front item from the queue
    if (isEmpty())
    {
        cout << "There is no soul to remove!\n";
    }
    else {
        _front = (_front + 1) % _size;
        _count--;
    }  
}

//to check if the queue is empty
bool Queue::isEmpty()
{
    return (size() == 0);
}

//to check if the queue is full
bool Queue::isFull()
{
    return (size() == _size);
}


//to return the queue size
int Queue::size()
{
    return _count;
}


string Queue::peek()
{
    //if empty print the message else return the front element of the queue
    if (isEmpty())
    {
        cout << "There is no soul to exchange\n";
        system("PAUSE");
        return "";
    }
    return _array[_front];
}


