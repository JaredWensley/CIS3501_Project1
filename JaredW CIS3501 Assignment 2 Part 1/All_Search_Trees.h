#ifndef BST_SEARCH_TREE_h
#define BST_SEARCH_TREE_h
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//structure for defining nodes of the binary search tree to be used as linked lists 
struct TreeNode {
	TreeNode* left = nullptr;		// Pointer to left node
	TreeNode* right = nullptr;		// Pointer to rigt node
	int info = 0;						// Holds value of the node
	int twin = 1;						// Tracks number of duplicate node values
	int height = 0;						// Holds the heigh of the node
};

//structure for tracking total comparison and creations for each operation. 
struct OperationCount {
	int comparisons = 0;
	int creations = 0;
	int deletes = 0;
	int inserts = 0;
	int searches = 0;

	vector<int> TotalSearch;
	vector<int> TotalInsert;
	vector<int> TotalCompar;
	vector<int> TotalCreate;
	vector<int> TotalDelete;
	//function to reset comparsion and creation counters
	void reset() {
		comparisons = 0;
		creations = 0;
		deletes = 0;
		searches = 0;
		inserts = 0;
	}
};
class BasicTree {
public:
	virtual void InsertItem(int item) = 0;
	virtual void DeleteItem(int item, ofstream& outfile) = 0;

	void ProcessInsertFile(string filename, ofstream& outputfile);
	void ProcessActionFile(string actionfile, ofstream& outputfile);
	void SearchItem(int& item, bool& found);
	void PrintTree(ofstream&, char OperationType);
	void OperationSummary(ofstream&, string);

protected:
	TreeNode* root;
	OperationCount opCount;
	int get_height(TreeNode* tree);
	void DeleteNode(TreeNode*& tree);
	void GetPredecessor(TreeNode* tree, int& item, int& twin_chain);
	void DeletePredecessor(TreeNode*& tree, int item);
	void Print(TreeNode* tree, ofstream& outfile, char);
	void preorder(TreeNode* tree, int depth, int left, int right, vector<vector<string>>& result);
	void Search(TreeNode* tree, int& item, bool& found);
	bool isValidCommand(char check);
};

// inherited from BasicTree, contains functions specific to BST tree
class BST : public BasicTree {
public:
	BST();
	void InsertItem(int item) override;
	void DeleteItem(int item, ofstream& outfile) override;

protected: 
	void Insert(TreeNode*& tree, int item);
	void Delete(TreeNode*& tree, int item, ofstream& outfile);
};

// inherited from BST, contains functions specific to AVL tree
class AVL : public BST {
public:
	AVL();
	void InsertItem(int item) override;
	void DeleteItem(int item, ofstream& outfile) override;

private:
	int getBalanceFactor(TreeNode* tree);
	void Insert(TreeNode*& tree, int item);
	void Delete(TreeNode*& tree, int item, ofstream& outfile);
	void SingleLeft(TreeNode*& tree);
	void SingleRight(TreeNode*& tree);
	void DoubleLeft(TreeNode*& tree);
	void DoubleRight(TreeNode*& tree);
	void BalanceTree(TreeNode*& tree);
};



#endif 










/*
// For part 2 figure out correct inheritence and reuse code that can be reused.
//Class for managing binary search tree functions
class BST {
public:
	BST();
	//int get_height(TreeNode* tree);
	//void InsertFile(string filename, ofstream& outputfile);
	//void ActionFile(string actionfile, ofstream& outputfile);
	//void preorder(TreeNode* tree, int depth, int left, int right, vector<vector<string>>& result);
	//void InsertItem(int);
	//void DeleteItem(int, ofstream& outfile);
	//void SearchItem(int& item, bool& found);
	//void PrintTree(ofstream&, char OperationType);
	//void OperationSummary(ofstream&, string);
	//OperationCount opCount;	//Brings operation counter into scope

private:
	//bool isValidCommand(char check);
	void Insert(TreeNode*& tree, int item);
	void Print(TreeNode* tree, ofstream& outfile, char);
	void Delete(TreeNode*& tree, int item, ofstream& outfile);
	void DeleteNode(TreeNode*& tree);
	void GetPredecessor(TreeNode* tree, int& item, int& twin_chain);
	void DeletePredecessor(TreeNode*& tree, int item);
	void Search(TreeNode* tree, int& item, bool& found);
	TreeNode* root;				//Pointer to the tree root.
};

// Class for managing self balacing tree
class AVL {
public:
	AVL();
	void DeleteItem(int, ofstream& outfile);
	void SearchItem(int& item, bool& found);
	void OperationSummary(ofstream& outputfile, string test_title);
	void ActionFile(string actionfile, ofstream& outputfile);
	void InsertFile(string filename, ofstream& outputfile);
	void SingleLeft(TreeNode*& tree);
	void SingleRight(TreeNode*& tree);
	void DoubleLeft(TreeNode*& tree);
	void DoubleRight(TreeNode*& tree);
	void BalanceTree(TreeNode*& tree);
	void InsertItem(int item);
	void PrintTree(ofstream&, char OperationType);
	void preorder(TreeNode* tree, int depth, int left, int right, vector<vector<string>>& result);
	OperationCount opCount;

private:
	bool isValidCommand(char check);
	void Print(TreeNode* tree, ofstream& outfile, char);
	int get_height(TreeNode* tree);
	void Insert(TreeNode*& tree, int item);
	int getBalanceFactor(TreeNode* tree);
	void Search(TreeNode* tree, int& item, bool& found);
	void Delete(TreeNode*& tree, int item, ofstream& outfile);
	void DeleteNode(TreeNode*& tree);
	void GetPredecessor(TreeNode* tree, int& item, int& twin_chain);
	void DeletePredecessor(TreeNode*& tree, int item);
	TreeNode* root;

};
*/


