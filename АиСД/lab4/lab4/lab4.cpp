#include "stdafx.h"
#include <iostream>
#include "vector"
#include "Graph.h"
#include "vld.h"

using namespace std;

const unsigned int  MaxGraphVer = 50;


int main(int argc, char* argv[]){
	setlocale(LC_ALL, "Russian");
	string fileName = argv[1];
	Graph graph(fileName, MaxGraphVer);
	int start;
	int end;
	cout << "¬ведите начальную точку: ";
	cin >> start;
	cout << endl;
	cout << "¬ведите конечную точку: ";
	cin >> end;
	graph.PrintPaths(start - 1, end - 1);
}

