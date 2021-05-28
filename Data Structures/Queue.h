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

	Queue() // Default Constructor
	{
		front = nullptr;
		back = nullptr;
	}

	Queue(T m_node) // Non-default constructor
	{
		Node<T>* newNode = new Node<T>*(m_node);
		front = newNode;
		back = nullptr;
	}

	bool IsEmpty() // checks if queue is empty.
	{
		return (front == nullptr);
	}

	void enqueue(T m_data) // adds node to the end of the list.
	{
		Node<T>* newNode = new Node<T>(m_data);

		if (IsEmpty()) // If this is the first node
		{
			front = newNode;
		}
		else
		{
			if (back == nullptr) // If this is the second node
			{
				back = newNode;
			}
			else
			{
				back->SetNext(newNode);
				back = newNode;
			}

		}
	}

	bool dequeue(T & return_data) // returns first node in the list.
	{
		if (IsEmpty()) return false; // If queue is empty return 

		Node<T>* Delete_Node = front; // temp ptr for the node to delete

		return_data = front->GetData();
		front = front->GetNext(); 

		if (Delete_Node == back) back = nullptr; // if node to delete is last one (special case)

		delete Delete_Node; // freeing memory

		return true;
	}


	bool peek(T & return_data) // returns a copy of the first node.
	{
		if (IsEmpty()) return false;
		
		return_data = front->GetData();
		
		return  true;
	}


	~Queue()
	{
		T del;
		while (dequeue(del));
	}
};