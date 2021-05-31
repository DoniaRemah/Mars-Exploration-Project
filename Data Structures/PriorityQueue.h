#pragma once
#include "PQNode.h"
template <typename T>
class PriorityQueue
{
private:
	PQNode<T>* front;
	PQNode<T>* back;
public:

	// All member Functions are to be defined here

	// Constructors

	PriorityQueue() // default constructor 
	{
		front = nullptr;
		back = nullptr;
	}

	PriorityQueue(T  m_data) // non-default constructor
	{
		PQNode<T>* newNode = new PQNode<T>(m_data); // creating Node
		front = newNode; 
		back = nullptr;
	}

	bool IsEmpty() // checks if queue is empty.
	{
		return (front == nullptr);
	}

	void enqueue(T m_data ,float prio) // adds node to the end of the list.
	{

		PQNode<T>* newNode = new PQNode<T>(m_data); // creating Node
		newNode->SetPriority(prio);

		if (IsEmpty())	//If this is the first Node.
			front = newNode;
		else
		{
			PQNode<T>* ptr = front;
			PQNode<T>* prev = front;

			float Prio_Ptr = 0;

			while (ptr)
			{
				Prio_Ptr = ptr->GetPriority();

				if (prio > Prio_Ptr)
				{
					if (ptr == front)
					{
						newNode->SetNext(ptr);
						front = newNode;
					}
					else
					{
						newNode->SetNext(ptr);
						prev->SetNext(newNode);
					}	
					break;
				}
				else if (!ptr->GetNext()) 
				{
					ptr->SetNext(newNode);
					newNode->SetNext(nullptr);
					break;
				}

				prev = ptr;
				ptr = ptr->GetNext();
			}

		}

		PQNode<T>* ptr = front;

		while (ptr) // getting value of back ptr
		{
			if (ptr->GetNext() == nullptr)
			{
				back = ptr;
				return;
			}
			ptr = ptr->GetNext();
		}
	}

	// returns first node in the list.

	bool dequeueFront(T & return_data) 
	{
		if (IsEmpty()) return false; // If queue is empty return 

		PQNode<T>* Delete_Node = front; // temp ptr for the node to delete

		return_data = front->GetData();

		front = front->GetNext();

		if (Delete_Node == back) back = nullptr; // if node to delete is last one (special case)

		delete Delete_Node; // freeing memory

		return true;
	}

	bool dequeueBack(T & return_data) // returns Last node in the list.
	{
		if (IsEmpty()) return false; // If queue is empty return 

		PQNode<T>* Delete_Node = back; // temp ptr for the node to delete

		return_data = back->GetData();

		if (back == front || back == nullptr) // If this is the last node.
		{
			front = nullptr;
		}
		else
		{
			PQNode<T>* Prev_Back = nullptr; // pointer to previous node to back
			PQNode<T>* ptr = front;

			while (ptr)
			{
				if (ptr->GetNext() == back) // checking if this is the previous node.
				{
					Prev_Back = ptr;
					break;
				}
				ptr = ptr->GetNext();
			}

			back = Prev_Back;
			back->SetNext(nullptr);
		}

		delete Delete_Node; // freeing memory

		return true;
	}

	bool peekFront(T & m_node) // returns a copy of the first node.
	{
		if (IsEmpty()) return false;
		m_node = front->GetData();
		return true;
	}

	bool peekBack(T& m_node)
	{
		if (IsEmpty()) return false;
		m_node = back->GetData();
		return true;
	}

	~PriorityQueue() // destructor
	{
		T del;
		while (dequeueFront(del));
	}
};