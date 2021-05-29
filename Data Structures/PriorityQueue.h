#pragma once
#include "Node.h"

template <typename T>
class PriorityQueue
{
private:
	Node<T>* front;
	Node<T>* back;
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
		Node<T>* newNode = new Node<T>(m_data); // creating Node
		front = newNode; 
		back = nullptr;
	}

	bool IsEmpty() // checks if queue is empty.
	{
		return (front == nullptr);
	}

	void enqueue(T m_data ,float prio) // adds node to the end of the list.
	{

		Node<T>* newNode = new Node<T>(m_data); // creating Node

		if (IsEmpty())	//If this is the first Node.
			front = newNode;
		else
		{
			Node<T>* ptr = front;
			Node<T>* prev = front;

			float Prio_Ptr = 0;

			while (ptr)
			{
				Prio_Ptr = ptr->GetPriority();

				if (prio >= Prio_Ptr)
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

				prev = ptr;
				ptr = ptr->GetNext();
			}

		}

		Node<T>* ptr = front;

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
	bool dequeueFront(T & return_data,int & prio_) // returns first node in the list.
	{
		if (IsEmpty()) return false; // If queue is empty return 

		Node<T>* Delete_Node = front; // temp ptr for the node to delete

		return_data = front->GetData();

		front = front->GetNext();
		prio_ = front->GetPriority();

		if (Delete_Node == back) back = nullptr; // if node to delete is last one (special case)

		delete Delete_Node; // freeing memory

		return true;
	}

	bool dequeueBack(T & return_data,int & prio_) // returns Last node in the list.
	{
		if (IsEmpty()) return false; // If queue is empty return 

		Node<T>* Delete_Node = back; // temp ptr for the node to delete

		return_data = back->GetData();
		prio_ = back->GetPriority();

		if (back == front || back == nullptr) // If this is the last node.
		{
			front = nullptr;
		}
		else
		{
			Node<T>* Prev_Back; // pointer to previous node to back
			Node<T>* ptr = front;

			while (ptr)
			{
				if (ptr->GetNext() == back) // checking if this is the previous node.
				{
					Prev_Back = ptr;
					return;
				}
				ptr = ptr->GetNext();
			}

			back = Prev_Back;
		}

		delete Delete_Node; // freeing memory

		return true;
	}

	bool peekFront(T & m_node) // returns a copy of the first node.
	{
		if (IsEmpty) return false;
		m_node = front;
		return true;
	}

	bool peekBack(T& m_node)
	{
		if (IsEmpty) return false;
		m_node = back;
		return true;
	}

	~PriorityQueue() // destructor
	{
		T del;;
		while (dequeueFront(del));
	}
};