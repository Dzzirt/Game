#include <vector>
#include <map>
#include <fstream>
#include <string>
#include "iostream"
#include "boost/algorithm/string.hpp"

struct Node
{
	bool isLeaf;
	Node * father;
	std::vector<int> mElements;
	Node * sons[5];

	Node();
	~Node();
};

struct BTree
{
	BTree(int degree);
	~BTree();
	std::string Find(int key);
	void Push(int key);
	void Fill(std::string & fileName);
	void Show();
private:
	int  mDegree;
	Node* mRoot;
	std::string mFileName;
	std::map<int, std::string> data;
	bool Searching(int key, Node * node);
	void Print(Node * node, int & depth);
	int Insert(Node* node, int key);
	Node* BalanceTree(Node * node, int key);
};

