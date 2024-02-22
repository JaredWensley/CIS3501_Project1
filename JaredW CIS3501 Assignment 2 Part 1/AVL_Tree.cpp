#include "All_Search_Trees.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <numeric>

using namespace std;

void AVL::InsertFile(string filename, ofstream& outputfile) {

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

// Default constuctor that sets root to NULL
AVL::AVL() {
	root = nullptr;
}

// Calls the Insert function
void AVL::InsertItem(int item) {
	Insert(root, item);
}

// Prints AVL tree
void AVL::PrintTree(ofstream& outfile, char OperationChar) {
	Print(root, outfile, OperationChar);
}

//Helper function. Inserts items into the AVL tree
void AVL::Insert(TreeNode*& tree, int item) {


	//if the current tree node location is NULL then create a new tree node
	if (tree == nullptr) {
		tree = new TreeNode;			//Node Creation
		tree->right = nullptr;			//Sets right child to NULL
		tree->left = nullptr;			//Sets left child to NULL
		tree->info = item;				//Sets the new nodes value to the param item
		opCount.comparisons++;
	}

	//if the item is equal to the nodes values then increase the nodes twin value by 1 
	else if (item == tree->info) {
		tree->twin = tree->twin + 1;	//Increase nodes twin value by 1
		opCount.comparisons++;			//Increase node comparisons variabe by 1
	}

	else if (item < tree->info) {
		opCount.comparisons++;			//Increase node comparisons variabe by 1
		Insert(tree->left, item);		//Recursive call with the next left node
	}

	else {
		opCount.comparisons++;			//Increase node comparisons variabe by 1
		Insert(tree->right, item);		//Recursive call with the next right node
	}

	
	// Set a new nodes height equal to 1
	if (tree->height == 0) {
		tree->height = 1;
	}

	// Find the new height of an already existing node. So we add a comparison
	else {
		tree->height = max(get_height(tree->right), get_height(tree->left)) + 1;
		opCount.comparisons++;
	}
	BalanceTree(tree);
}

// Helper function returns the height of the tree
int AVL::get_height(TreeNode* tree) 
{
	if (tree == nullptr) {
		return 0;
	}
	return tree->height;
}

// Helper Function to insert: gets nodes balance factor
int AVL::getBalanceFactor(TreeNode* tree) 
{
	if (tree == nullptr) {
		return 0;
	}
	else {
		return(get_height(tree->left) - (get_height(tree->right)));
	}
}

//
void AVL::BalanceTree(TreeNode*& tree)
{
	int BF = getBalanceFactor(tree);


	if (BF > 1) {

		if (getBalanceFactor(tree->left) >= 0) {
			// LEFT-LEFT scenario. Rotate Right once
			
			cout << "right rotate" << endl;
			SingleRight(tree);
		}
		else {
			// LEFT-RIGHT scenario. Rotate left then right
			cout << "doubleright" << endl;
			DoubleRight(tree);
		}
	}
	else if (BF < -1) {

		if (getBalanceFactor(tree->right) <= 0) {
			// RIGHT-RIGHT scenario. Rotate left once
			cout << "left rotate" << endl;
			SingleLeft(tree);
		}
		else {
			// RIGHT-LEFT scenario. Rotate right then left
			cout << "double left" << endl;
			DoubleLeft(tree);
		}
	}
}

// RIGHT-RIGHT imbalance scenario
void AVL::SingleLeft(TreeNode*& tree)
{
	TreeNode* temp = tree->right;
	tree->right = temp->left; 	opCount.comparisons++;	// operation
	temp->left = tree;			opCount.comparisons++;  // operation

	tree->height = max(get_height(tree->left), get_height(tree->right)) + 1;
	temp->height = max(get_height(temp->left), get_height(temp->right)) + 1;

	tree = temp;				opCount.comparisons++;  // operation
}

// LEFT-LEFT imbalance scenario
void AVL::SingleRight(TreeNode*& tree)
{
	TreeNode* temp = tree->left;
	tree->left = temp->right;	opCount.comparisons++;	// operation
	temp->right = tree;			opCount.comparisons++;	// operation

	tree->height = max(get_height(tree->left), get_height(tree->right)) + 1;
	temp->height = max(get_height(temp->left), get_height(temp->right)) + 1;

	tree = temp;				opCount.comparisons++;	// operation
}

// RIGHT-LEFT imbalance scenario
void AVL::DoubleLeft(TreeNode*& tree)
{
	SingleRight(tree->right);
	SingleLeft(tree);
}

// LEFT-RIGHT imbalance scenario
void AVL::DoubleRight(TreeNode*& tree)
{
	SingleLeft(tree->left);
	SingleRight(tree);
}

// Prints the AVL tree
void AVL::Print(TreeNode* tree, ofstream& outfile, char OperationType) {
	//Finds the height and width of the tree
	int h = tree->height;
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

// Keeps track of all operations in the function
void AVL::OperationSummary(ofstream& outputfile, string test_title) {

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

//Recursive Helper Function converts the binary search tree into a vector of string vectors in preorder(VLR).
void AVL::preorder(TreeNode* tree, int depth, int left, int right, vector<vector<string>>& result)
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



