// CS303 - Assignment 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Functions.h"
#include "Queue.h"

int main()
{
	// Display welcome message
	string title = "Welcome to: CS303 - Assignment 3";
	int titleFormat = (102 - title.length())/2;
	cout << string(titleFormat, ' ') << title << endl;
	cout << '!' << string(100, '=') << '!' << endl;

	//Initialize queue
	ifstream dataFile("data.txt");
	Queue<int> intQueue; //Inital queue for integers
	Queue<string> strQueue; //Inital queue for integers
	Queue<float> floQueue; //Inital queue for integers

	if (!dataFile.good()) {
		cout << "Inital dataFile not good!" << endl;
		return 1; 
	}

	readFile(dataFile, intQueue);

	//Menu
	mainMenu(intQueue, strQueue, floQueue);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
