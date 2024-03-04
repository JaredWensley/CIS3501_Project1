#include "All_Search_Trees.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <numeric>
using namespace std;

// Default constructor
AVL::AVL() {
	root = nullptr;uj
}

// Inserts an number into the AVL tree
void AVL::InsertItem(int item) {
	Insert(root, item);
}

// Deletes a number from the AVL tree
void AVL::DeleteItem(int item, ofstream& outfile) {
	Delete(root, item, outfile);
}

// Helper: Inserts a number then checks for reblanace
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

// Helper: deletes a node then checks for rebalance.
void AVL::Delete(TreeNode*& tree, int item, ofstream& outfile) {

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

	BalanceTree(tree);
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


// Helper: Rebalances the AVL tree 
void AVL::BalanceTree(TreeNode*& tree)
{
	int BF = getBalanceFactor(tree);


	if (BF > 1) {

		if (getBalanceFactor(tree->left) >= 0) {
			// LEFT-LEFT scenario. Rotate Right once
			SingleRight(tree);
		}
		else {
			// LEFT-RIGHT scenario. Rotate left then right
			
			DoubleRight(tree);
		}
	}
	else if (BF < -1) {

		if (getBalanceFactor(tree->right) <= 0) {
			// RIGHT-RIGHT scenario. Rotate left once
			SingleLeft(tree);
		}
		else {
			// RIGHT-LEFT scenario. Rotate right then left
			DoubleLeft(tree);
		}
	}
}


// Helper: RIGHT-RIGHT imbalance scenario
void AVL::SingleLeft(TreeNode*& tree)
{
	TreeNode* temp = tree->right;
	tree->right = temp->left; 	opCount.comparisons++;	// operation
	temp->left = tree;			opCount.comparisons++;  // operation

	tree->height = max(get_height(tree->left), get_height(tree->right)) + 1;
	temp->height = max(get_height(temp->left), get_height(temp->right)) + 1;

	tree = temp;				opCount.comparisons++;  // operation
}


// Helper: LEFT-LEFT imbalance scenario
void AVL::SingleRight(TreeNode*& tree)
{
	TreeNode* temp = tree->left;
	tree->left = temp->right;	opCount.comparisons++;	// operation
	temp->right = tree;			opCount.comparisons++;	// operation

	tree->height = max(get_height(tree->left), get_height(tree->right)) + 1;
	temp->height = max(get_height(temp->left), get_height(temp->right)) + 1;

	tree = temp;				opCount.comparisons++;	// operation
}


// Helper: RIGHT-LEFT imbalance scenario
void AVL::DoubleLeft(TreeNode*& tree)
{
	SingleRight(tree->right);
	SingleLeft(tree);
}


// Helper: LEFT-RIGHT imbalance scenario
void AVL::DoubleRight(TreeNode*& tree)
{
	SingleLeft(tree->left);
	SingleRight(tree);
}











