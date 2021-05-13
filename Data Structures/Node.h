#pragma once

template <typename T>
class Node
{
private:
	T data;
	Node* <T> Next; // Initially set to Null

public:

	// All member Functions are to be defined here

	Node(T d); // Constructor

	//Setters
	void SetNext(T n);
	void SetData(T d);

	//Getters
	Node* GetNext();
	T GetData();

	~Node(); // Destructor
};