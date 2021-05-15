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

	// Constructors 

	Queue(); // default constructor
	Queue(const T& m_node); // Non-default constructor

	void enqueue(const T& m_data); // adds node to the end of the list.
	bool dequeue(Node<T>* m_node); // returns first node in the list.

	void peek(Node<T>* m_node); // returns a copy of the first node.

	~Queue();
};