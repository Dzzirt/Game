#include "BTree.h"

using namespace std;


BTree::BTree(int minDegree)
{
	mRoot = new Node();
	mDegree = minDegree;
	mRoot->isLeaf = true;
	mRoot->father = nullptr;
}

BTree::~BTree()
{

}

std::string BTree::Find(int key)
{
	if (Searching(key, mRoot))
	{
		return data.at(key);
	}
	else
	{
		Insert(mRoot, key);
		BalanceTree(mRoot, key);
		cout << "Данных не существует, введите имя нового элемента: ";
		string val;
		cin >> val;
		data.insert(pair<int, string>(key, val));
		ofstream out(mFileName, std::ios_base::app);
		out << key << ":" << val << endl;
		out.close();
		system("cls");
		Show();
		cout << endl;
		return "Элемент добавлен!";
	}
}

bool BTree::Searching(int key, Node * node)
{
	int counter = 0;
	while (counter != node->mElements.size())
	{
		if (node->mElements[counter] > key && !node->isLeaf)
		{
			return Searching(key, node->sons[counter]);
		}
		if (node->mElements[counter] == key)
		{
			return true;
		}
		counter++;
	}
	if (!node->isLeaf)
	{
		return Searching(key, node->sons[node->mElements.size()]);
	}
	else
	{
		return false;
	}
}

void BTree::Push(int key)
{
	Insert(mRoot, key);
}

void BTree::Fill(std::string & fileName)
{
	mFileName = fileName;
	ifstream in(fileName);	
	while (!in.eof())
	{
		string line;
		getline(in, line);
		vector<string> splited;
		boost::split(splited, line, boost::is_any_of(":"));
		if (!line.empty())
		{
			data.insert(std::pair<int, std::string>(stoi(splited[0]), splited[1]));
			Push(stoi(splited[0]));
		}

	}
}

void BTree::Print(Node * node, int & depth)
{
	if (node)
	{
		for (int i = 0; i < depth ; i++)
		{
			cout << "-";
		}
		auto print = [](int key)
		{
			std::cout << " " << key;
		};
		for_each(node->mElements.begin(), node->mElements.end(), print);
		cout << endl;
		int nodeSonsLen = sizeof(node->sons) / sizeof(*node->sons);
		for (int i = 0; i < nodeSonsLen; i++)
		{
			depth++;
			Print(node->sons[i], depth);
			depth--;
		}
	}
}

void BTree::Show()
{
	int depth = 1;
	Print(mRoot, depth);
}

int BTree::Insert(Node* node, int key)
{
	if (node)
	{
		node = BalanceTree(node, key);
		if (node->mElements.size() == 0)
		{
			node->mElements.push_back(key);
			return node->mElements.size() - 1;
		}
		else
		{
			int counter = 0;
			while (counter != node->mElements.size())
			{
				if (node->mElements[counter] > key)
				{
					break;
				}
				counter++;
			}
			if (node->isLeaf)
			{
				if (counter == node->mElements.size())
				{
					node->mElements.push_back(key);
					return node->mElements.size() - 1;
				}		
				node->mElements.insert(node->mElements.begin() + counter, key);
				return counter;
			}
			else
			{
				Insert(node->sons[counter], key);
			}
			
		}
	}
}

Node* BTree::BalanceTree(Node * node, int key)
{
	if (node->mElements.size() >= mDegree)
	{
		if (!node->father)
		{
			node->father = new Node();
			node->father->father = nullptr;
			node->father->isLeaf = false;
			mRoot = node->father;
		}
		node->father = BalanceTree(node->father, key);
		int middleKeyPos = int((node->mElements.size() - 1) / 2);
		int middleKey = node->mElements[middleKeyPos];
		int counter = 0;
		while (counter != node->father->mElements.size())
		{
			if (node->father->mElements[counter] > middleKey)
			{
				break;
			}
			counter++;
		}
		if (counter == node->father->mElements.size())
		{
			node->father->mElements.push_back(middleKey);
		}
		else
		{
			node->father->mElements.insert(node->father->mElements.begin() + counter, middleKey);
		}
		
		Node * left = new Node();
		Node * right = new Node();
		left->isLeaf = node->isLeaf;
		right->isLeaf = node->isLeaf;
		left->father = node->father;
		right->father = node->father;
		int nodeSonsLen = sizeof(node->sons) / sizeof(*node->sons);
		copy(node->sons, node->sons + middleKeyPos + 1, left->sons);
		copy(node->sons + middleKeyPos + 1, node->sons + nodeSonsLen, right->sons);
		left->mElements = vector<int>(node->mElements.begin(), node->mElements.begin() + middleKeyPos);
		right->mElements = vector<int>(node->mElements.begin() + middleKeyPos + 1, node->mElements.end());
		node->father->sons[counter] = left;
		node->father->sons[counter + 1] = right;
		for_each(node->sons, node->sons + middleKeyPos + 1, [&](Node * node) 
		{
			if (node)
			{
				node->father = left;
			}

		});
		for_each(node->sons + middleKeyPos + 1, node->sons + nodeSonsLen, [&](Node * node)
		{
			if (node)
			{
				node->father = right;
			}
		});
		Node * father = node->father;
		delete node;
		if (middleKey > key)
		{
			return left;
		}
		else
		{
			return right;
		}
	}
	return node;
}

Node::Node()
{
	int nodeSonsLen = sizeof(sons) / sizeof(*sons);
	for (int i = 0; i < nodeSonsLen ; i++)
	{
		sons[i] = nullptr;
	}
}

Node::~Node()
{

}
