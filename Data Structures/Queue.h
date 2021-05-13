#pragma once
#include"Node.h"

template<typename T>
class Queue
{
private:
	Node<T>* front;
	Node<T>* back;

public:

	// All member Functions are to be defined here
	Queue();


	~Queue();
};