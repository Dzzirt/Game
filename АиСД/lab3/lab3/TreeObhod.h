#pragma once

#include "fstream" 

const int DL = 20;          // максимальная длина

struct Tree {
	char name[DL];
	int urov;
	Tree *fath;         // отец в исходном дереве
	Tree *left;
	Tree *right;
};

int read_from_file(FILE *F, Tree **r);  // чтение из файла, формирование дерева
void back_from_bin(Tree *p);            // выдача исходное дерева из бинарного 
void print_down_bin(Tree *p, int lev);  // выдача бинарного сверху вниз
void print_up_bin(Tree *p, int lev);    // выдача бинарного снизу вверх
void print_right_bin(Tree *p, int lev); // выдача бинарного слева направо