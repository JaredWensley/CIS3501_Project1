#include "All_Search_Trees.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <numeric>

using namespace std;

// Constructor for BST which initializes the root as null
BST::BST() {
	root = nullptr;
}

// Inserts an item into the BST
void BST::InsertItem(int item) {
	Insert(root, item);
}

// Deletes an item in the BST from the Action file. 
void BST::DeleteItem(int item, ofstream& outfile) {
	Delete(root, item, outfile);
}

//Recursive Helper Function that inserts a number into the binary search tree
void BST::Insert(TreeNode*& tree, int item)
{

	//if the current tree node location is NULL then create a new tree node
	if (tree == nullptr) {
		tree = new TreeNode;			//Node Creation
		tree->right = nullptr;			//Sets right child to NULL
		tree->left = nullptr;			//Sets left child to NULL
		tree->info = item;				//Sets the new nodes value to the param item
		tree->twin = 1;					//Sets the new nodes twin value to 1
		tree->height = 0;
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

	// Set a new nodes height equal to 1
	if (tree->height == 0) {
		tree->height = 1;
	}

	// Find the new height of an already existing node. So we add a comparison
	else {
		tree->height = max(get_height(tree->right), get_height(tree->left)) + 1;
		opCount.comparisons++;
	}

}

//Helper function that finds node to delete
void BST::Delete(TreeNode*& tree, int item, ofstream& outfile) {

	// If the item does not exist in the tree
	if (tree == nullptr) {
		outfile << item << " not found: printing current tree" << endl;
		cout << item << " not found: printing current tree" << endl;
		opCount.comparisons++;
		return;
	}

	// traverse to the LEFT node if the items value is less than the current nodes value
	if (item < tree->info) {
		Delete(tree->left, item, outfile);
		opCount.comparisons++;
	}

	// traverse to the RIGHT node if the items value is creater than the current nodes value
	else if (item > tree->info) {
		Delete(tree->right, item, outfile);
		opCount.comparisons++;
	}

	// Decrease the nodes twin value by one if its value is creater than one
	else if (tree->twin > 1) {
		tree->twin = tree->twin - 1;
		opCount.deletes++;
		opCount.comparisons++;
	}

	// Calls function to delete current node. At this point there is no twin chain value.
	else {
		DeleteNode(tree);
	}
}

// Helper function: Deletes predecessor from GetPredecessor()
void BST::DeletePredecessor(TreeNode*& tree, int item) {

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
