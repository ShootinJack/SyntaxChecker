#include <iostream>
#include <fstream>
#include <string>
#include "GenStack.h"
#pragma once
using namespace std;

class UserInterface
{
private:
	ifstream code;
	GenStack<char> stack;
	int lineCount, lastC, lastP, lastB, selection;
	string filename;
	bool select;
public:
	UserInterface();
	UserInterface(string);
	~UserInterface();
	void parceFile();
	void throwError(int, char);
	void rePromptUser();
	void runScript();
};

