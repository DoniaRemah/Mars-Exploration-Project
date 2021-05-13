#pragma once
#include "Node.h"

template <typename T>
class  LinkedList
{
private:
	Node* <T> Head;
	Node* <T> Tail;

public:
	// All member Functions are to be defined here

	LinkedList(); // Constructor

	// Setters
	void SetHead(Node* H);
	void SetTail(Node* T);

	// Getters
	Node* GetHead();
	Node* GetTail();


	// Delete 

	void DeleteAll();
	bool DeleteNode(Node* m_node); // Searches for node and deletes it. if found returns true otherwise false

	// Insert

	~LinkedList(); // Destructor

};