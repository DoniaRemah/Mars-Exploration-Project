#pragma once

template <typename T>
class Node
{
private:
	T data;
	Node* <T> Next; // Initially set to Null

public:

	// All member Functions are to be defined here

	// Constructors 

	Node(); // defualt constructor (omittable)
	Node(T d); // Non-defualt Constructor

	//Setters
	void SetNext(Node<T>* n);
	void SetData(T d);

	//Getters
	Node<T>* GetNext();
	T GetData();

	~Node(); // Destructor
};