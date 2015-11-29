#pragma once
#include "TreeObhod.h"
#include <fstream>

void PrintLevel(const Tree &  current, int curr_pos);

void PreviousCatalog(Tree *&  current, int & curr_pos);

void NextCatalog(Tree *&  current, int & curr_pos);

Tree* GetTreeFromFile(char const* arg);

void CreateCatalog(Tree*& current, Tree*& fath);

void StepInto(Tree*& current, Tree*& fath);

void StepOut(Tree*& current, Tree*& fath);

void ChangeName(Tree*& current);

void DestroyBranch(Tree *&p);

void CopyBranch(Tree*& from, Tree*& to);

void SetFather(Tree*& curr, Tree *& fath);

void SetLevel(Tree *& curr);

void PrintHelp();

void DeleteCatalog(Tree *& current, Tree *& fath);

void Copy(Tree *& copy_val, Tree*& current);

void Paste(Tree*& current, Tree*& copy_val, Tree*& fath);

bool CheckPastePossibility(Tree* copy_val, Tree*& current);

void TreeSave(Tree *p, std::ofstream & fout);