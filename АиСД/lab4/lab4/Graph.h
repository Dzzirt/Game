#include <vector>
#include "Cell.h"
#include "fstream"
#include "iostream"
#include "string"
#include "map"
#include "boost/algorithm/string.hpp"

typedef std::vector<std::vector<int>> Paths;

struct Graph{
	Graph(const std::string & physEffects, const std::string & physElements, int vertCount);
	~Graph();
	void FindAndSavePath(size_t start, size_t end, std::string & output);

	void GenerateReport(std::vector<std::vector<int>> &paths, std::string & output);

private:
	std::map<int, std::string> mVertexes;
	std::vector<std::vector<Cell*>> mMatrix;
	std::vector<bool> mVisitedVert;
	int mVertCount;

	void LoadVertexNamesFromFile(const std::string & fileName);
	void DFS(std::vector<int> &path, size_t & start, size_t end, Paths &paths);
	void Fill(const std::string & physEffects, const std::string & physElements);
	void Create();
};