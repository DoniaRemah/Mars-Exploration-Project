#pragma once
#include "Node.h"

template <typename T>
class PriorityQueue
{
private:
	Node<T>* front;
public:

	// All member Functions are to be defined here

	// Constructors

	PriorityQueue(); // default constructor 
	PriorityQueue(T m_data); // non-default constructor


	void enqueue(const T& m_data); // adds node to the end of the list.
	bool dequeue(Node<T>* m_node); // returns first node in the list.

	void peek(Node<T>* m_node); // returns a copy of the first node.

	~PriorityQueue(); // destructor
};