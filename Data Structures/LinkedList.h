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

	// Setters (Omittable)
	void SetHead(Node<T>* H);
	void SetTail(Node<T>* T);

	// Getters (One is omittable)
	Node<T>* GetHead();
	Node<T>* GetTail();


	// Delete 

	void DeleteAll(); // Deletes all nodes
	bool DeleteNode(const Node<T>* m_node); // Searches for node and deletes it. if found returns true otherwise false
	bool DeleteFirst(); // Deletes first node in the list
	bool DeleteLast(); // Deletes last node in the list (Omittable)

	// Insert
	bool InsertEnd(const T m_newdata); // Inserts node at the end of the list
	bool InsertBeg(const T m_newdata); // Inserts node at the beg of the list

	// find (One of them is omittable)

	bool find_Node(Node<T>* return_node); // searches for a certain node. returns true and the node if found otherwise returns false and a nullptr
	Node<T>* find_Data(T m_data); // finds a node carrying the data. If not found returns nullptr

	~LinkedList(); // Destructor

};