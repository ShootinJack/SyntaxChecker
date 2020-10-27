#include <iostream>
#include <fstream>
#include <string>
#include "UserInterface.h"
using namespace std;

int main(int argc, char** argv ) { // takes argument from command line
	string filename;
	ifstream inFile;
	if (argv[1] != NULL) {
		filename = argv[1];
	}
	else
	{
		cout << "Please enter your filename: "; // if no command line gets file name here
		cin >> filename;
	}
	do {
		inFile.open(filename); // makes sure file  name works
		if (inFile.good() == true) {
			continue;
		}
		else {
			cout << "Invalid filename\nEnter Another: ";
			cin >> filename;
		}
	} while (inFile.good() != true);

	UserInterface *Checker = new UserInterface(filename); // runs parcer
	Checker->parceFile();

	delete Checker;
	system("pause");
	return 0; // ends program
}