#include "UI.h"
using namespace std;
#include<iostream>
#include<string>

void UI::OutputStr(string str)
{
	cout << str << endl;

}

string UI::getInput()
{
	string str;
	cin >> str;
	return str;
}
