#include "stdafx.h"
#include <iostream>
#include "vector"
#include "Graph.h"

using namespace std;

const unsigned int  MaxGraphVer = 50;


int main(int argc, char* argv[]){
	setlocale(LC_ALL, "Russian");
	string physEffect = argv[1];
	string physElements = argv[2];
	string output = argv[3];
	Graph graph(physEffect, physElements, MaxGraphVer);
	int start;
	int end;
	cout << "¬ведите начальную точку: ";
	cin >> start;
	cout << endl;
	cout << "¬ведите конечную точку: ";
	cin >> end;
	graph.FindAndSavePath(start - 1, end - 1, output);
}

