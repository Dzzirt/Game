#include "TreeObhod.h"
#include "fs_functions.h"
#include <iostream>
#include "sstream"

using namespace std;

/* ����������  �  ������  ��  �������  ������   ����������
��������  �  �������  ������.  ���������� ���������� ���������
��������:
   1) �������� ������ � ������ �� �����;
   2) ����� ������ ����� �  ������  �������  (��������� �����,
      ������ �� ������� � �. �.); 
   3) �������������  ������ ��� �������� ����� ����� � ������,
�� ��������������, �����������, �������� � ��������. 
   4) ���������� ������ � ����� (13).
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
	Tree* fath = root;
	Tree* copy_val = nullptr;
	bool paste_failed = false;
	int curr_pos = 0;
	PrintLevel(*current, curr_pos);
	int input = -1;
	while (input != '\t')
	{
		if (input == 'c')
		{
			cout << "������� ��� ������ ��������: ";
			CreateCatalog(current, fath);
		}
		else if (input == 'z')
		{
			if (CheckPastePossibility(copy_val, fath))
			{
				Paste(current, copy_val, fath);
			}
			else
			{
				paste_failed = true;
			}
		}
		else if (input == 'x')
		{
			if (current != nullptr)
			{
				copy_val = current;
			}
		}
		else if (input == 'd')
		{
			DeleteCatalog(current, fath);
		}
		else if (input == 'r')
		{
			cout << "������� ����� ��� ��������: ";
			ChangeName(current);
		}
		else if (input == 'q')
		{
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
		system("cls");
		if (paste_failed)
		{
			cout << "����� ���������� �������� ��������� �������� �����!" << endl << endl;
			paste_failed = false;
		}
		if (current != nullptr)
		{
			PrintLevel(*current->fath->left, curr_pos);
		}
		else
		{
			PrintHelp();
			cout << "������� ����" << endl;
		}
		cout << endl << "������� ����� �������: ";
		input = cin.get();
		cin.ignore();
	}
	cout << "���������� ������..." << endl << endl;
	ofstream fout(argv[1], ios_base::trunc);
	TreeSave(root, fout);
	fout.close();
	return 0;
}
