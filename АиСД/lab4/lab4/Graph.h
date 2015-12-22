#include <vector>
#include "Cell.h"
#include "fstream"
#include "iostream"
#include "string"
#include "boost/algorithm/string.hpp"

typedef std::list<std::vector<int>> Paths;

struct Graph{
	Graph(const std::string & fileName, int vertCount);
	~Graph();
	void PrintPaths(size_t start, size_t end);

private:
	std::vector<std::vector<Cell*>> mMatrix;
	std::vector<bool> visitedVert;
	int mVertCount;

	void DFS(std::vector<int> &path, size_t & start, size_t end, std::list<std::vector<int>> &paths);
	void Fill(const std::string & fileName);
	void Create();
};