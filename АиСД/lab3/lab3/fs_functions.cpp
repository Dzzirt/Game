#include "fs_functions.h"
#include <iostream>

using namespace std;

void PrintLevel(const Tree& current, int curr_pos)
{
	PrintHelp();
	int counter = 0;
	Tree* ptr = new Tree();
	*ptr = current;
	while (ptr != nullptr)
	{
		if (counter == curr_pos)
		{
			cout << ptr->name << "  <--" << endl;
			counter++;
		}
		else
		{
			counter++;
			cout << ptr->name << endl;
		}
		ptr = ptr->right;
	}
	delete ptr;
}

void PreviousCatalog(Tree*& current, int& curr_pos)
{
	if (curr_pos != 0)
	{
		current = current->fath->left;
		int counter = 0;
		curr_pos--;
		while (counter != curr_pos)
		{
			current = current->right;
			counter++;
		}
	}
}

void NextCatalog(Tree*& current, int& curr_pos)
{
	if (current != nullptr)
	{
		if (current->right != nullptr) {
			curr_pos++;
			current = current->right;
		}
		
	}
}

Tree* GetTreeFromFile(char const* arg)
{
	Tree* root = nullptr;
	FILE* Fin;
	Fin = fopen(arg, "r");
	if (Fin == nullptr)
	{
		return root;
	}
	read_from_file(Fin, &root);
	return root;
}

void CreateCatalog(Tree*& current, Tree*& fath)
{
	if (current == nullptr)
	{
		current = new Tree();
		current->fath = fath;
		current->urov = fath->urov + 1;
		cin.getline(current->name, DL);
		current->fath->left = current;
	}
	else
	{
		Tree* temp = current->right;
		current->right = new Tree();
		current->right->fath = current->fath;
		current->right->urov = current->urov;
		current->right->right = temp;
		cin.getline(current->right->name, DL);
	}
}

void StepInto(Tree*& current, Tree*& fath)
{
	if (current != nullptr)
	{
		fath = current;
		current = current->left;
	}
}

void StepOut(Tree*& current, Tree*& fath)
{
	if (fath->urov != 0)
	{
		current = fath->fath->left;
		fath = current->fath;
	}
}

void ChangeName(Tree*& current)
{
	cin.getline(current->name, DL);
}

void PrintHelp()
{
	cout << "w: UP | s: DOWN  | e: STEP INTO | q: STEP OUT | " << endl;
	cout << "c: NEW| d: DELETE| x: COPY      | z: PASTE    | r: RENAME|" << endl << endl;
}

void DestroyBranch(Tree*& p)
{
	if (p)
	{
		DestroyBranch(p->left);
		DestroyBranch(p->right);
		delete p;
	}
}

void CopyBranch(Tree*& from, Tree*& to)
{
	if (from)
	{
		to = new Tree();
		*to = *from;
		CopyBranch(from->left, to->left);
		CopyBranch(from->right, to->right);
	}
}

void SetFather(Tree*& curr, Tree*& fath)
{
	if (curr)
	{
		curr->fath = fath;
		SetFather(curr->left, curr);
		SetFather(curr->right, fath);
	}
}

void SetLevel(Tree*& curr)
{
	if (curr)
	{
		curr->urov = curr->fath->urov + 1;
		SetLevel(curr->left);
		SetLevel(curr->right);
	}
}

void DeleteCatalog(Tree*& current, Tree*& fath, int& curr_pos)
{
	if (current != nullptr) {
		fath = current->fath;
		DestroyBranch(current->left);
		if (curr_pos == 0) {
			if (current->right != nullptr) {
				fath->left = current->right;
			}
			else {
				fath->left = nullptr;
			}
		}
		else if (current->right == nullptr) {
			SetNullBrother(fath, curr_pos);
		}
		else {
			SetNextBrother(fath, curr_pos);
		}
		delete current;
		current = fath->left;
		curr_pos = 0;
	}
	
}

void SetNullBrother(Tree*& fath, int curr_pos)
{
	int pos = 0;
	Tree* father_ptr = fath->left;
	while (pos != curr_pos - 1)
	{
		father_ptr = father_ptr->right;
		pos++;
	}
	father_ptr->right = nullptr;
}

void SetNextBrother(Tree*& fath, int curr_pos)
{
	int pos = 0;
	Tree* current = fath->left;
	while (pos != curr_pos - 1)
	{
		current = current->right;
		pos++;
	}
	current->right = current->right->right;
}

void Copy(Tree*& copy_val, Tree*& current)
{
	if (copy_val->left != nullptr)
	{
		CopyBranch(copy_val->left, current->left);
		SetFather(current->left, current);
		SetLevel(current->left);
	}
	else
	{
		current->left = nullptr;
	}
}

void Paste(Tree*& current, Tree*& copy_val, Tree*& fath)
{
	if (copy_val != nullptr)
	{
		if (current == nullptr)
		{
			current = new Tree();
			current->fath = fath;
			current->urov = fath->urov + 1;
			current->fath->left = current;
			memcpy(current->name, copy_val->name, sizeof(current->name));
			Copy(copy_val, current);
		}
		else
		{
			Tree* temp = current->right;
			current->right = new Tree();
			current->right->fath = current->fath;
			current->right->urov = current->urov;
			current->right->right = temp;
			memcpy(current->right->name, copy_val->name, sizeof(current->right->name));
			Copy(copy_val, current->right);
		}
	}
}

bool CheckPastePossibility(Tree* copy_val, Tree*& current)
{
	if (current->urov != 0)
	{
		if (current->name == copy_val->name)
		{
			return false;
		}
		if (!CheckPastePossibility(copy_val, current->fath))
		{
			return false;
		}
	}
	return true;
}

void TreeSave(Tree* p, ofstream& fout)
{
	string st;
	if (p)
	{
		for (int i = 0; i < p->urov; i++) st.append(".");
		string name(p->name);
		st.append(name + "\n");
		fout.write(st.c_str(), st.size());
		TreeSave(p->left, fout);
		TreeSave(p->right, fout);
	}
}
