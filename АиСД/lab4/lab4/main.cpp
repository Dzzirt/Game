#include <iostream>
using namespace std;
const int n = 5;
int i, j;
bool *visited = new bool[n];
//������� ��������� �����
int graph[n][n] =
{
	{ 0, 1, 0, 0, 1 },
	{ 1, 0, 1, 1, 0 },
	{ 0, 1, 0, 0, 1 },
	{ 0, 1, 0, 0, 1 },
	{ 1, 0, 1, 1, 0 }
};
//����� � �������
void DFS(int st)
{
	int r;
	cout << st + 1 << " ";
	visited[st] = true;
	for (r = 0; r <= n; r++)
		if ((graph[st][r] != 0) && (!visited[r]))
			DFS(r);
}
//������� �������
void main()
{
	setlocale(LC_ALL, "Rus");
	int start;
	cout << "������� ��������� �����: " << endl;
	for (i = 0; i < n; i++)
	{
		visited[i] = false;
		for (j = 0; j < n; j++)
			cout << " " << graph[i][j];
		cout << endl;
	}
	cout << "��������� ������� >> "; cin >> start;
	//������ ���������� ������
	bool *vis = new bool[n];
	cout << "������� ������: ";
	DFS(start - 1);
	delete[]visited;
	system("pause>>void");
}