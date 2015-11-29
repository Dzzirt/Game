#include "TreeObhod.h"
#include "fs_functions.h"
#include <iostream>
#include "sstream"

using namespace std;

/* Информация  о  файлах  на  жестких  дисках   компьютера
записана  с  помощью  дерева.  Обеспечить выполнение следующих
операций:
   1) загрузку дерева в память из файла;
   2) обход дерева папок в  режиме  диалога  (раскрыиме папок,
      подъем на уровень и т. п.); 
   3) корректировку  дерева при создании новых папок и файлов,
их переименовании, копировании, переносе и удалении. 
   4) сохранение дерева в файле (13).
*/


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("\nUsage: filemanager.exe <input.txt>");
		getchar();
		return -1;
	}
	setlocale(LC_ALL, "rus");
	Tree* root = GetTreeFromFile(argv[1]);
	if (root == nullptr)
	{
		printf("\nCan not open file %s", argv[1]);
		getchar();
		return -1;
	}


	//=========================================


	Tree* current = root->left;
	Tree* fath = nullptr;
	Tree* copy_val = nullptr;
	int curr_pos = 0;
	PrintLevel(*current, curr_pos);
	int input = -1;
	while (input != '\t')
	{
		if (input == 'c')
		{
			cout << "Введите имя нового каталога: ";
			CreateCatalog(current, fath);
		}
		else if (input == 'z')
		{
			if (current == nullptr) {
				current = new Tree();
				current->fath = fath;
				current->urov = fath->urov + 1;
				current->fath->left = current;
				memcpy(current->name, copy_val->name, sizeof(current->name));
				if (copy_val->left != nullptr) {
					CopyBranch(copy_val->left, current->left);
					SetFather(current->left, current);
				}
				else {
					current->left = nullptr;
				}
			}
			else {
				Tree* temp = current->right;
				current->right = new Tree();
				if (copy_val->left != nullptr) {
					CopyBranch(copy_val->left, current->right->left);
					SetFather(current->right->left, current->right);
				}
				else
				{
					current->right->left = nullptr;
				}
				current->right->fath = current->fath;
				current->right->urov = current->urov;
				current->right->right = temp;
				memcpy(current->right->name, copy_val->name, sizeof(current->right->name));
			}
		}
		else if (input == 'x') {
			copy_val = current;

		}
		else if (input == 'd') {
			DeleteCatalog(current, fath);
		}
		else if (input == 'r') {
			cout << "Введите новое имя каталога: ";
			ChangeName(current);
		}
		else if (input == 'q') {
			StepOut(current, fath);
			curr_pos = 0;
		}
		else if (input == 'e')
		{
			StepInto(current, fath);
			curr_pos = 0;
		}
		else if (input == 's')
		{
			NextCatalog(current, curr_pos);
		}
		else if (input == 'w')
		{
			PreviousCatalog(current, curr_pos);
		}

		if (current != nullptr)
		{
			PrintLevel(*current->fath->left, curr_pos);
			back_from_bin(root);
		}
		else
		{
			system("cls");
			PrintHelp();
			cout << "Каталог пуст" << endl;
		}
		cout << endl << "Введите номер команды: ";
		input = cin.get();
		cin.ignore();
	}
	cout << "Завершение работы..." << endl << endl;
	return 0;
}
