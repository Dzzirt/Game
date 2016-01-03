#include "BTree.h"

void UsingTree(BTree &tree, std::string fileName)
{
	tree.Fill(fileName);
	int input;
	tree.Show();
	std::cout << std::endl;
	std::cout << "������� ����: ";
	std::cin >> input;
	while (input != -1)
	{
		if (input < 0)
		{
			std::cout << "���� �� ����� ���� �������������!" << std::endl;
		}
		else
		{
			system("cls");
			tree.Show();
			std::cout << std::endl;
			std::cout << "��������� ������: " << tree.Find(input) << std::endl;
		}
		std::cout << "������� ����: ";
		std::cin >> input;
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	int maxSons = 3;
	BTree tree(maxSons);
	std::string inputFileName = argv[1];
	UsingTree(tree, inputFileName);
	return 0;
}

