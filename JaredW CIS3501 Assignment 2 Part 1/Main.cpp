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

	string treetype;



	//Enter Test name
	cout << "Enter the Title of this Test: ";
	getline(cin, test_title);
	cout << endl;

	// Prompt the user for the insert file name
	cout << "Enter Insert file name excluding the .txt: ";
	getline(cin, InsertFile);
	InsertFile = InsertFile + ".txt";
	cout << endl;

	/*
	// Prompt the user for the action file name
	cout << "Enter Action file name excluding the .txt: ";
	getline(cin, ActionFile);
	ActionFile = ActionFile + ".txt";
	cout << endl;
	*/

	string outputfilename;
	//prompt the user to enter the name of the outputfile
	cout << "Note, file can not be made if the file name contains: / \\ : ? * \" < > |" << endl;
	cout << "Enter output file name excluding the .txt: ";
	getline(cin, outputfilename);
	outputfilename = outputfilename + ".txt";
	cout << endl;

	cout << "Type BST or AVL to choose which search tree to use" << endl;
	cin >> treetype;

	ofstream output(outputfilename);

	// Check for errors and insert file items
	//bst.InsertFile(InsertFile, output);
	//bst.ActionFile(ActionFile, output);

	avl.InsertFile(InsertFile, output);

	//print report
	//bst.OperationSummary(output, test_title);
	avl.OperationSummary(output, test_title);
}








