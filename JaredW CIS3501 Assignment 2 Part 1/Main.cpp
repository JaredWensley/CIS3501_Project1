// JaredW CIS3501 Assignment 2 Part 1.cpp : 
#include "All_Search_Trees.h"
using namespace std;

int main()
{
	//Declare necessary Variables and objects
	string InsertFile;
	string test_title;
	string ActionFile;
	BST bst;
	AVL avl;
	string TreeType;

	//Enter Test name
	cout << "Enter the Title of this Test: ";
	getline(cin, test_title);
	cout << endl;

	// Pick which tree to run
	cout << "Type either AVL, BST: ";
	getline(cin, TreeType);


	BasicTree* tree = nullptr; // Pointer to the base class

	if (TreeType == "BST") {
		tree = new BST(); // Dynamically create a BST
	}
	else if (TreeType == "AVL") {
		tree = new AVL(); // Dynamically create an AVL
	}
	else {
		cout << "Error: Check your spelling of your tree type; must be BST or AVL";
		return 1;
	}


	// Prompt the user for the insert file name
	cout << "Enter Insert file name excluding the .txt: ";
	getline(cin, InsertFile);
	InsertFile = InsertFile + ".txt";
	cout << endl;

	// Prompt the user for the action file name
	cout << "Enter Action file name excluding the .txt: ";
	getline(cin, ActionFile);
	ActionFile = ActionFile + ".txt";
	cout << endl;


	string outputfilename;
	//prompt the user to enter the name of the outputfile
	cout << "Note, file can not be made if the file name contains: / \\ : ? * \" < > |" << endl;
	cout << "Enter output file name excluding the .txt: ";
	getline(cin, outputfilename);
	outputfilename = outputfilename + ".txt";
	cout << endl;



	ofstream output(outputfilename);
	

	// use 'tree' to call the functions
	tree->ProcessInsertFile(InsertFile, output);
	tree->ProcessActionFile(ActionFile, output);
	tree->OperationSummary(output, test_title);

	delete tree; 
	output.close(); 

	
	
}








