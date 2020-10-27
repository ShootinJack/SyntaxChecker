#include "UserInterface.h"



UserInterface::UserInterface() // Default Constructor
{
	rePromptUser();
}

UserInterface::UserInterface(string n) // Overloaded Constructor getting filename from user
{
	filename = n;
	lastP = 0;
	lastC = 0;
	lastB = 0;
}


UserInterface::~UserInterface() // Default destructor, nothing to delete
{

}

void UserInterface::parceFile() // This function goes through the file looking for delimeters pushing them into the stack
{								// once a pair is found it will check against the stack
	string line;
	code.open(filename);
	lineCount = 0;
	while (code.good()) {
		lineCount++;
		getline(code, line);
		for (int i = 0; i < line.length(); ++i) {	
			switch (line[i]) {
			case '{':
				stack.push('{');
				lastC = lineCount;
				break;
			case'(':
				stack.push('(');
				lastP = lineCount;
				break;
			case'[':
				stack.push('[');
				lastB = lineCount;
				break;
			case'}':
				if (stack.isEmpty()) {
					throwError(lineCount, '{');
					cout << "No Opening Brace\n";
					return;
				}
				else if (stack.peek() == '(') {
					stack.pop();
					throwError(lastP, ')');
					return;
				}
				else if (stack.peek() == '[') {
					stack.pop();
					throwError(lastB, ']');
					return;
				}
				else {
					stack.pop();
				}
				break;
			case')':
				if (stack.isEmpty()) {
					throwError(lineCount, '(');
					cout << "No Opening Brace\n";
					return;
				}
				else if (stack.peek() == '{') {
					stack.pop();
					throwError(lastC, '}');
					return;
				}
				else if (stack.peek() == '[') {
					stack.pop();
					throwError(lastB, ']');
					return;
				}
				else {
					stack.pop();
				}
				break;
			case']':
				if (stack.isEmpty()) {
					throwError(lineCount, '[');
					return;
				}
				else if (stack.peek() == '(') {
					stack.pop();
					throwError(lastP, ')');
					return;
				}
				else if (stack.peek() == '{') {
					stack.pop();
					throwError(lastC, '}');
					return;
				}
				else {
					stack.pop();
				}
				break;
			}

		}
	}
	code.close();
	if (stack.isEmpty()) {
		rePromptUser();
	}
	else {
		switch (stack.pop()) {
		case'(':
			throwError(lastP, ')');
			break;
		case'[':
			throwError(lastB, ']');
			break;
		case'{':
			throwError(lastC, '}');
			break;
		}
	}
}

void UserInterface::throwError(int l, char c) // function showing user where and what the error is
{
	cout << "Error: Line " << l << " - Expected: " << c << endl;
}

void UserInterface::rePromptUser() // function reprompting user for another file if there where no errors
{
	select = true;
	cout << "No Errors!\n";
	while (select) {
		cout << "Do you want to check another file ? \n1) Yes\n2) No\nSelection: ";
		cin >> selection;
		if (cin.fail()) {
			cout << "Use correct data type.\n";
			cin.clear();
			cin.ignore();
		}
		else if (selection < 1 || selection > 2) {
			cout << "Please pick 1 or 2\n";
		}
		else if(selection == 1) {
			select = false;
			runScript();
		}
		else if (selection == 2) {
			select = false;
		}
	}
	
}

void UserInterface::runScript() // function getting the filename and re running parce file to keep the loop going
{
	cout << "Please enter your filename: ";
	cin >> filename;
	do {
		code.open(filename);
		if (code.good() == true) {
			continue;
		}
		else {
			cout << "Invalid filename\nEnter Another: ";
			cin >> filename;
		}
	} while (code.good() != true);
	parceFile();
}
