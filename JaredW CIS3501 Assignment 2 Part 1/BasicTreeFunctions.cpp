//Jared Wensley CIS3501 Assignment 2 part 1
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <numeric>
#include "All_Search_Trees.h"
using namespace std;

// Calls functions dependent on each line from the action file whie checking for errors
void BasicTree::ProcessActionFile(string actionfilename, ofstream& outputfile) {
	bool found;
	ifstream actionfile(actionfilename);
	string line;
	int lineNumber = 0;

	// Checks if the file can open
	if (!actionfile.is_open()) {
		cerr << "Error opening file: " + actionfilename << ": Please check your filename" << endl;
		outputfile << "Error opening file: " + actionfilename << ": Please check your filename" << endl;
		return;
	}
	
	// Check if the file is empty
	if (actionfile.peek() == ifstream::traits_type::eof()) {
		cerr << "Error: The file " + actionfilename + " is empty, please enter a different file" << endl;
		outputfile << "Error: The file " + actionfilename + " is empty, please enter a different file" << endl;
		return;
	}

	// Calls functions and handles errors for each line in the action file
	while (getline(actionfile, line)) {
		lineNumber++; // Increment line number

		//Handle Error: Line is empty
		if (line.empty()) continue;


		// Handle Error: if the first character is not a letter
		if (!isalpha(line[0])) {
			cerr << "Error on line " << lineNumber << ": First character is not a letter, skipping line" << endl;
			cerr << "Error on line " << lineNumber << ": First character is not a letter, skipping line" << endl;
			;
		}

		//Changes each lines first character to lower case letter
		char action = tolower(line[0]);

		// Hanlde Error: Checks if the letter command is valid or not
		if (!isValidCommand(action)) {
			cerr << "Error on line " << lineNumber << " of Action file: Invalid character, skipping line." << endl;
			outputfile << "Error on line " << lineNumber << " of Action file: Invalid character, skipping line. " << endl;
			continue;
		}

		stringstream ss(line.substr(1)); // To read from the rest of the line
		int num;
		char extra;

		// Hanlde Error: If there is no number after the command character
		if (!(ss >> num)) {
			cerr << "Error on line " << lineNumber << " of action file: Missing or invalid argument after command. Skipping line." << endl;
			outputfile << "Error on line " << lineNumber << " of action file: Missing or invalid argument after command. Skipping line." << endl;
			continue;
		}
		// Handle Error: Extra character found after number,
		else if (ss >> extra) {
			cerr << "Error on line " << lineNumber << " of action file: Missing or invalid argument after command. Skipping line." << endl;
			outputfile << "Error on line " << lineNumber << " of action file: Missing or invalid argument after command. Skipping line." << endl;
			continue;
		}

		// Continue to call insert, delte or search functions
		else {

			char D = 'D';
			char I = 'I';
			char S = 'S';
			switch (action) {
			case 'i':

				outputfile << "Insert: " << num << endl << endl;
				cout << "Insert: " << num << endl << endl;


				// Call insert function
				// no need for empty tree check
				opCount.inserts++;
				InsertItem(num);

				PrintTree(outputfile, I);
				break;

			case 'd':

				// Call delete function
				outputfile << "Delete: " << num << endl << endl;
				cout << "Delete: " << num << endl << endl;
				DeleteItem(num, outputfile);

				// Check if the 
				opCount.comparisons++;
				if (root == nullptr) {
					outputfile << endl;
					cout << endl;
					outputfile << "TREE IS EMPTY" << endl;
					cout << "TREE IS EMPTY" << endl;
				}
				PrintTree(outputfile, D);
				break;

			case 's':


				// Call search function
				SearchItem(num, found);
				outputfile << "Search: " << num << endl << endl;
				cout << "Search: " << num << endl << endl;

				// If tree is empty
				opCount.comparisons++;
				if (root == nullptr) {
					outputfile << endl;
					cout << endl;
					outputfile << "TREE IS EMPTY" << endl;
					cout << "TREE IS EMPTY" << endl;
				}
				// If the number was not found in the Binary Search Tree
				else if (!found) {
					outputfile << num << " not found: printing current tree" << endl;
					cout << num << " not found: printing current tree" << endl;
				}

				//Print the Binary Search Tree
				PrintTree(outputfile, S);
				break;

			default:
				cerr << "Error: No functions were called" << endl;
				outputfile << "Error: No functions were called" << endl;
				return;
			}
		}
	}
}

// Inserts integers from file into the binary search tree while checking for errors
void BasicTree::ProcessInsertFile(string filename, ofstream& outputfile) {

	ifstream insertfile(filename);	//Input file stream
	string line;					// String to hold each line of input
	int lineNumber = 0;				// Track line numbers for error messages

	// Check if the file can open
	if (!insertfile.is_open()) {
		cerr << "Error opening file: " + filename << endl;
		outputfile << "Error opening file: " + filename << endl;
		return; // Stop the operation
	}

	// Check if the file is empty
	if (insertfile.peek() == ifstream::traits_type::eof()) {
		cerr << "Error: The file " + filename + " is empty, please enter a different file" << endl;
		outputfile << "Error: The file " + filename + " is empty, please enter a different file" << endl;
		return; // Stop the operation
	}

	char C = 'C';
	// Read from the file line by line
	while (getline(insertfile, line)) {
		lineNumber++; // Increment line number

		// Use a stringstream to read from the line
		stringstream ss(line);

		// Attempt to read a number from the line
		int num; //temp storage
		if (!(ss >> num)) {
			// If extraction fails, report an error and continue to the next line
			cerr << "Error: Non-integer data found on line " << lineNumber << " in the InsertFile " << filename << ". Skipping line." << endl;
			outputfile << "Error: Non-integer data found on line " << lineNumber << " in the InsertFile " << filename << ". Skipping line." << endl;
			continue;
		}

		// Check if there's anything else on the line after the integer
		string extra;
		if (ss >> extra) {
			// If extra data is found after the integer, report an error and continue to the next line
			cerr << "Error: More than one token found on line " << lineNumber << " in the Insertfile " << filename << ". Skipping line." << endl;
			outputfile << "Error: More than one token found on line " << lineNumber << " in the Insertfile " << filename << ". Skipping line." << endl;
			continue;
		}

		// No errors encountered; insert the number into the binary search tree and print each iteration
		opCount.creations++;
		InsertItem(num);
		outputfile << "Insert: " << num << endl << endl;
		cout << "Insert: " << num << endl << endl;
		PrintTree(outputfile, C);
	}

	insertfile.close();		//Close input file stream
}

// Searches for an item i the BST from the Action file
void BasicTree::SearchItem(int& item, bool& found) {
	Search(root, item, found);
}

// Prints the BST and resets all counters
void BasicTree::PrintTree(ofstream& outfile, char OperationType) {
	Print(root, outfile, OperationType);
}

// Helper function for the action file function
bool BasicTree::isValidCommand(char check) {
	return check == 'i' || check == 'd' || check == 's';
}

// Helper function that Deletes the node passed in
void BasicTree::DeleteNode(TreeNode*& tree) {
	int item;
	int twin_chain;

	//temp pointer variable used to delete
	TreeNode* tempPtr;
	tempPtr = tree;

	// If the current node has 0 or 1 children. No left node
	if (tree->left == nullptr) {
		tree = tree->right;
		delete tempPtr;
		opCount.deletes++;
		opCount.comparisons++;
	}
	// If the current node has 0 or 1 children. No right node
	else if (tree->right == nullptr) {
		tree = tree->left;
		delete tempPtr;
		opCount.deletes++;
		opCount.comparisons++;
	}
	// If the current node has 2 children. Calls function to get replacement for deleted node
	else {
		opCount.comparisons++;
		GetPredecessor(tree->left, item, twin_chain);		// Find ideal replacement
		tree->info = item;									// Sets node equal to replacement items value					 
		tree->twin = twin_chain;							// Sets node equal to replacement items twin value.
		DeletePredecessor(tree->left, item);				// Delete it's old position	
	}
}

// Helper function: Gets correct replacement node. Finds the left right most node to retreive
void BasicTree::GetPredecessor(TreeNode* tree, int& item, int& twin_chain) {
	while (tree->right != nullptr) {
		tree = tree->right;
		opCount.comparisons++;
	}
	twin_chain = tree->twin;
	item = tree->info;
}

/*
// Helper function: Deletes predecessor from GetPredecessor()
void BasicTree::DeletePredecessor(TreeNode*& tree, int item) {

	// traverse to the LEFT node if the items value is less than the current nodes value
	if (item < tree->info) {
		opCount.comparisons++;
		DeletePredecessor(tree->left, item);
	}

	// traverse to the RIGHT node if the items value is creater than the current nodes value
	else if (item > tree->info) {
		opCount.comparisons++;
		DeletePredecessor(tree->right, item);
	}
	// Delete the node
	else {
		tree->twin = 1;		// Set twin value to default to delete the complete node
		DeleteNode(tree);
	}

}
*/

// Recursive Helper Function that searches for an number in the tree. 
void BasicTree::Search(TreeNode* tree, int& item, bool& found) {

	// If the node is not found
	if (tree == nullptr) {
		found = false;
		opCount.comparisons++;
	}
	// If the items value is less than the current tree nodes values, traverse left
	else if (item < tree->info) {
		Search(tree->left, item, found);
		opCount.comparisons++;
	}
	// If the items value is greater than the current tree nodes values, traverse right
	else if (item > tree->info) {
		Search(tree->right, item, found);
		opCount.comparisons++;
	}
	// if the item is equal to the current tree node.
	else if (item == tree->info) {
		found = true;
		opCount.comparisons++;
	}
}

// Helper Function that prints the binary search tree
void BasicTree::Print(TreeNode* tree, ofstream& outfile, char OperationType)
{
	//Finds the height and width of the tree
	int h;
	if (tree == nullptr) {
		h = 0;
	}
	else {
		h = tree->height;
	}
	int w = pow(2, h) - 1;

	//Creates a vector of string vectors used to convert the tree from linked lists. 
	vector<vector<string>> stringBST(h, vector<string>(w, " "));

	//Converts the binary search tree from linked lists to vectors and corretlly formats.
	preorder(tree, 0, 0, w - 1, stringBST);

	//Prints the binary search tree using the above vector
	for (const auto& row : stringBST) {
		for (const auto& spot : row) {
			outfile << spot << " ";
			cout << spot << " ";
		}
		outfile << endl;
		cout << endl;

		for (int i = 0; i < w; ++i) { // Creates a space between each level
			outfile << " ";
			cout << " ";
		}
		outfile << endl;
		cout << endl;
	}
	outfile << endl;
	cout << endl;

	//Outputs the height of the tree and the operations during this iteration
	outfile << "Height: " << h << endl;
	cout << "Height: " << h << endl;
	outfile << "Operations: " << opCount.comparisons + opCount.creations + opCount.deletes + opCount.inserts << "   [";
	cout << "Operations: " << opCount.comparisons + opCount.creations + opCount.deletes + opCount.inserts << "   [";

	// Display comparisons if they were in this iteration
	if (opCount.comparisons > 0) {
		outfile << "Compare:" << opCount.comparisons << " ";
		cout << "Compare:" << opCount.comparisons << " ";
	}
	// Display Creations if they were in this iteration
	if (opCount.creations > 0) {
		outfile << "create:" << opCount.creations << " ";
		cout << "create:" << opCount.creations << " ";
	}
	// Display Deletes if they were in this iteration
	if (opCount.deletes > 0) {
		outfile << "Delete:" << opCount.deletes << " ";
		cout << "Delete:" << opCount.deletes << " ";
	}
	// Display Inserts if they were in this iteration
	if (opCount.inserts > 0) {
		outfile << "Insert:" << opCount.inserts << " ";
		cout << "Insert:" << opCount.inserts << " ";
	}

	outfile << "]" << endl;
	cout << "]" << endl;

	//Creates a barrier between each iteration within the output file. Increases with the size of the tree
	if (w > 25) {
		string divider(w * 2, '_');
		outfile << divider << endl;
		cout << divider << endl;
	}
	else {
		outfile << "__________________________________" << endl;
		cout << "__________________________________" << endl;
	}


	// Keeps count of total count of each operation for end of file summary.
	if (OperationType == 'S') {
		opCount.TotalSearch.push_back(opCount.searches);
		opCount.TotalSearch.push_back(opCount.comparisons);
	}

	if (OperationType == 'C') {
		opCount.TotalCreate.push_back(opCount.creations);
		opCount.TotalCreate.push_back(opCount.comparisons);
	}

	if (OperationType == 'D') {
		opCount.TotalDelete.push_back(opCount.deletes);
		opCount.TotalDelete.push_back(opCount.comparisons);
	}

	if (OperationType == 'I') {
		opCount.TotalInsert.push_back(opCount.inserts);
		opCount.TotalInsert.push_back(opCount.comparisons);
	}

	//Resets the operations counter
	opCount.reset();
}

// Recursive Helper Function converts the binary search tree into a vector of string vectors in preorder(VLR).
void BasicTree::preorder(TreeNode* tree, int depth, int left, int right, vector<vector<string>>& result)
{
	//Base Case: Returns if the current node is NULL
	if (tree == nullptr) return;

	//Calculates the middle index for this depth level
	int mid = (left + right) / 2;

	//if the current node has a twin value then add that value to the nodes print
	if (tree->twin > 1) {
		result[depth][mid] = to_string(tree->info) + "-" + to_string(tree->twin);
	}
	//if the current node does not have a twin value then print the value
	else if (tree->twin == 1) {
		result[depth][mid] = to_string(tree->info);
	}

	//Recursively traverse the left and right subtrees in preorder, increasing depth for each level.
	//Functions also format the tree from top to bottom, in a pyramid shape. 
	preorder(tree->left, depth + 1, left, mid - 1, result);
	preorder(tree->right, depth + 1, mid + 1, right, result);
}

// Recursive Helper Function that finds the height of the binary search tree
int BasicTree::get_height(TreeNode* tree) {
	if (tree == nullptr) {
		return 0;
	}
	return tree->height;
}

// Prints out all Operation counters
void BasicTree::OperationSummary(ofstream& outputfile, string test_title) {

	//Declare variables
	int total;
	int SearchSum;
	int CreateSum;
	int DeleteSum;
	int InsertSum;

	// Accumulate every instance of the operation into a variable 
	SearchSum = accumulate(opCount.TotalSearch.begin(), opCount.TotalSearch.end(), 0);
	CreateSum = accumulate(opCount.TotalCreate.begin(), opCount.TotalCreate.end(), 0);
	InsertSum = accumulate(opCount.TotalInsert.begin(), opCount.TotalInsert.end(), 0);
	DeleteSum = accumulate(opCount.TotalDelete.begin(), opCount.TotalDelete.end(), 0);

	// Get the total ammount of operations
	total = SearchSum + CreateSum + InsertSum + DeleteSum;

	// Print operation Report
	outputfile << "                 " << test_title << endl << endl;
	outputfile << "Creation:        " << CreateSum << endl << endl;
	outputfile << "Search:          " << SearchSum << endl << endl;
	outputfile << "Insert:          " << InsertSum << endl << endl;
	outputfile << "Delete:          " << DeleteSum << endl << endl;
	outputfile << "               _____" << endl;
	outputfile << "Total            " << total << endl;


	cout << "                 " << test_title << endl << endl;
	cout << "Creation:        " << CreateSum << endl << endl;
	cout << "Search:          " << SearchSum << endl << endl;
	cout << "Insert:          " << InsertSum << endl << endl;
	cout << "Delete:          " << DeleteSum << endl << endl;
	cout << "               _____" << endl;
	cout << "Total            " << total << endl;


}