#pragma once

template <typename T>
class PQNode
{
private:
	T data;
	PQNode<T>* Next;
	float Priority;
public:

	// All member Functions are to be defined here

	// Constructors 

	PQNode() // defualt constructor (omittable)
	{
		Next = nullptr;
		Priority = 0;
	}

	PQNode(T d) // Non-defualt Constructor
	{
		data = d;
		Next = nullptr;
	}

	//Setters
	void SetNext(PQNode<T>* n)
	{
		Next = n;
	}

	void SetData(T d)
	{
		data = d;
	}

	void SetPriority(float  p)
	{
		Priority = p;
	}

	//Getters
	PQNode<T>* GetNext()
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

	~PQNode() // Destructor
	{

	}
};

