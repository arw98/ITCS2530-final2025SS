/*
Name: Erica (Athena) Watkins
Class: ITCS 2530 H0850 2025SS
Github Repo URL: https://github.com/arw98/ITCS2530-final2025SS.git
Summary: Bracelet Pattern Generator using C++ that lets users create unique designs with colors & symbols.
Your posted hobby/interest: Bracelet Making!
AI Tool(s) Used: ChatGPT
*/

#include <iostream> // header file library; I/O operations
#include <fstream>  // read from/write to external files
#include <string>	// string library
#include <cstdlib>	// chapter 5: rand(), srand() generate & seeding random #s
#include <ctime>	// chapter 5 : for time()
#include <iomanip>	// setw(n): width of next field printed; setfill(char): fill empty space w/ given char

using namespace std;// use names for objects/variables from standard library

// user defined struct to represent a bead
struct Bead {

	string color;	// bead color ROYGBV, etc.
	char symbol;	// bead symbol *, ^, #, etc.
};

// define class to rep bead pattern
class Bracelet {

private:				// data encapsulation to maintain consistency & integrity

	Bead pattern[100];	// holds up to 100 beads; stores pattern
	int length;			// length of pattern

public:

	Bracelet() {		// default constructor w/o parameters
		length = 0;		// initialize pattern length to 0 bc user has not gen pattern yet
	}

	// randomly generate bracelet pattern
	void generatePattern(Bead beads[], int count, int userLength) {

		length = userLength;				// pattern length chosen by user

		for (int i = 0; i < length; ++i) {	// loop through beads
			int random = rand() % count;	// choose random bead index
			pattern[i] = beads[random];		// assign random bead index to the pattern
		}
	}

	// display bracelet pattern to console & save pattern to a file
	void displayAndSavePattern() {
		
		cout << "\nGenerated Bracelet Pattern:\n\n" << endl;
		
		for (int i = 0; i < length; ++i) {
			cout << "{" << pattern[i].color << " - " << pattern[i].symbol << "}\n" << endl;
		}
		
		cout << endl;

		// ask user if they would like to save the file first
		char saveFile;

		cout << "Would you like to save this pattern to a file? (Y/N): ";	//obtain user input
		cin >> saveFile;
		saveFile = toupper(saveFile);	// convert to uppercase

		if (saveFile == 'Y') {			// if user input is yes

			string filename;
			cout << "Enter filename to save the pattern (example: pattern.txt): ";
			cin >> filename;

			ofstream outFile;			// file stream object
			outFile.open(filename);		// opens output file

			if (outFile) {
				for (int i = 0; i < length; ++i) {
					outFile << pattern[i].color << " " << pattern[i].symbol << endl;
				}
				outFile.close();		// close file
				cout << "Pattern saved to " << filename << "\n\n";
			}
			else {
				cerr << "Could not write to file :[" << "\n\n";
			}
		}
		else {
			cerr << "Pattern not saved :[\n\n";
		}
	}
};

// display menu to user
void showMenu() {

	// header
	const int width = 35;
	const string header = "Bracelet Pattern Generator";

	// top
	cout << string(width, '*') << endl;

	// mid
	int padding = (width - header.length()) / 2;
	cout << string(padding, '*') << header << string(width - padding - header.length(), '*') << endl;

	// bottom
	cout << string(width, '*') << endl;

	// menu
	cout << setfill(' ') << left;
	cout << setw(4) << "1. " << "Load Bead Colors From File" << endl;
	cout << setw(4) << "2. " << "Generate Bracelet Pattern" << endl;
	cout << setw(4) << "3. " << "Display and Save Pattern" << endl;
	cout << setw(4) << "4. " << "Exit Program" << endl;
	cout << string(width, '*') << endl;

	// ask for user input
	cout << setfill(' ') << "Enter your choice(1-4): ";
}

// this function gets # from user's menu choice
int getUserChoice() {

	int choice;
	cin >> choice;
	while (choice < 1 || choice > 4) {	// validate user input
		cout << "Invalid choice. Enter integer from 1-4.";
		cin >> choice;					// have user try again if invalid choice
	}
	return choice;						// function sends value stored in choice to where function was called
}

// this function loads bead data from the file into an array
int loadBeads(Bead beads[]) {

	string filename;
	cout << "Enter bead file name (example: beads.txt): ";
	cin >> filename;

	ifstream inFile;
	inFile.open(filename);	// open input file

	int count = 0;

	if (inFile) {

		while (inFile >> beads[count].color >> beads[count].symbol && count < 100) {
			count++;		// increment count; add each bead into array
		}
		inFile.close();		// close file
		// update user
		cout << count << " beads successfully loaded from file.\n\n";
	}
	else {
		cerr << "Error: Could not open file :[\n\n";
	}
	return count;			// return the amount of beads that were loaded
}

// run Program \(^_^)/
void runProgram() {

	Bead beads[100];					// array that holds bead data from file
	int count = 0;						// amount of beads loaded
	Bracelet bracelet;					// Bracelet object; instance of class

	srand(time(0));						// seed random num generator

	bool menu = true;					// menu loop

	while (menu) {
		showMenu();						// call function
		int choice = getUserChoice();	// obtain user input

		switch (choice) {				// expression evaluated then value used to choose/perform actions specificied by case

		case 1:
			count = loadBeads(beads);	// load bead data
			break;						// statement executes until eitehr break is found or end of switch structure reached

		case 2:
			if (count == 0) {			// validate input
				cout << "Please load bead colors first.\n\n";
			}
			else {						// obtain + validate user input
				int length;
				cout << "Enter desired bead length (1-100): ";
				cin >> length;
				while (length < 1 || length > 100) {
					cout << "Invalid length. Enter length 1-100: ";
					cin >> length;		// user tries again
				}
				bracelet.generatePattern(beads, count, length);	// generate bracelet by passing parameters
				cout << "Bracelet pattern generated.\n\n";		// update user of success
			}
			break;

		case 3:
			bracelet.displayAndSavePattern();					// display & save bead pattern
			break;

		case 4:
			cout << "Bye!\n";
			menu = false;				// end loop
			break;
		}
	}
}

// main function
int main() {
	runProgram();	// begin program
	return 0;		// successful prog w/ no errors!
}

