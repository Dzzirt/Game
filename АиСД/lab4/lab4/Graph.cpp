#include "Graph.h"
#include "SafeDelete.h"
using namespace std;


typedef std::list<std::vector<int>> Paths;

Graph::Graph(const std::string & fileName, int vertCount)
{
	mVertCount = vertCount;
	Create();
	Fill(fileName);
}

void Graph::PrintPaths(size_t start, size_t end)
{
	std::list<std::vector<int>> paths;
	std::vector<int> path;
	DFS(path, start, end, paths);
	if (paths.size() != 0)
	{
		auto bySize = [](const std::vector<int> & i, const std::vector<int> & j)
		{
			return (i.size() < j.size());
		};
		paths.sort(bySize);
		auto print = [](int vertex)
		{
			cout << vertex << " ";
		};
		auto printAll = [&](const vector<int> & vec)
		{
			for_each(vec.begin(), vec.end(), print);
			cout << endl;
		};
		for_each(paths.begin(), paths.end(), printAll);
	}
	else
	{
		cout << "Путь не существует" << endl;
	}
}

void Graph::DFS(std::vector<int> &path, size_t & start, size_t end, std::list<std::vector<int>> &paths)
{
	path.push_back(start + 1);
	visitedVert[start] = true;
	for (unsigned int r = 0; r < mMatrix.size(); r++){
		Cell * cell = mMatrix[start][r];
		if ((cell->isLinked) && (!visitedVert[r])){
			if (r == end)
			{
				path.push_back(end + 1);
				if (path.size() > 6)
				{
					break;
				}
				paths.push_back(path);
			}
			else
			{
				DFS(path, r, end, paths);
			}
			path.pop_back();
		}
	}
}

void Graph::Fill(const std::string & fileName)
{
	ifstream in(fileName);
	while (!in.eof())
	{
		string currentLine;
		std::getline(in, currentLine);
		std::vector<string> splited;
		boost::split(splited, currentLine, boost::is_any_of(";"));
		Cell * cell = mMatrix[stoi(splited[1]) - 1][stoi(splited[2]) - 1];
		cell->Add(splited[0]);
	}
}

void Graph::Create()
{
	mMatrix.reserve(mVertCount);
	for (int i = 0; i < mVertCount; i++)
	{
		vector<Cell*> cells;
		cells.reserve(50);
		mMatrix.push_back(cells);
		visitedVert.push_back(false);
		for (int j = 0; j < mVertCount; j++)
		{
			mMatrix[i].push_back(new Cell());
		}
	}
}

Graph::~Graph()
{
	auto vecDelete = [](std::vector<Cell*> & vec)
	{
		for_each(vec.begin(), vec.end(), SafeDelete<Cell>); 
	};
	for_each(mMatrix.begin(), mMatrix.end(), vecDelete);
}

