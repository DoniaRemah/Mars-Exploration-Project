#include "UI.h"
using namespace std;
#include<iostream>
#include<string>
#include"../Defs.h"

void UI::OutputStr(string str)
{
	cout << str << endl;

}

string UI::getInput()
{
	string str;
	//using getline to consider any spaces in line name
	getline(cin, str);
	return str;
}



UI::UI() 
{

}
void UI::ReadMode() 
{
	int m;
	cout << "Choose the mode: " << endl;
	cout << "------------------------------" << endl;
	cout << "1: Interactive Mode " << endl;
	cout << "2: Step by Step Mode " << endl;
	cout << "3: Silent Mode " << endl;
	cin >> m;
	if (m == 1 || m == 2 || m == 3) 
	{
		mode = m;
	}
	else 
	{
		while (m != 1 && m != 2 && m != 3)
		{
			cout << "Wrong number, please enter again: " << endl;
			cin >> m;
		}
	}
		
	     
}