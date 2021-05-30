#pragma once

template <typename T>
class Node
{
private:
	T data;
	Node<T>* Next;
	float Priority;
public:

	// All member Functions are to be defined here

	// Constructors 

	Node() // defualt constructor (omittable)
	{
		Next = nullptr;
		Priority = 0;
	}

	Node(T d) // Non-defualt Constructor
	{
		data = d;
		Next = nullptr;
	}

	//Setters
	void SetNext(Node<T>* n)
	{
		Next = n;
	}

	void SetData(T d)
	{
		data = d;
	}

	void SetPriority( float  p)
	{
		Priority = p;
	}

	//Getters
	Node<T>* GetNext()
	{
		return Next;
	}

	T GetData()
	{
		return data;
	}

	float GetPriority()
	{
		return Priority;
	}



	~Node() // Destructor
	{

	}
};

