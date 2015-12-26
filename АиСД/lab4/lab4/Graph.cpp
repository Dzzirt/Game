#include "Graph.h"
#include "SafeDelete.h"
using namespace std;


typedef std::vector<std::vector<int>> Paths;

Graph::Graph(const std::string & physEffects, const std::string & physElements, int vertCount)
{
	mVertCount = vertCount;
	Create();
	Fill(physEffects, physElements);
	LoadVertexNamesFromFile(physElements);
}

void Graph::LoadVertexNamesFromFile(const string & fileName)
{
	ifstream in(fileName);
	while (!in.eof())
	{
		string currentLine;
		getline(in, currentLine);
		std::vector<string> splited;
		boost::split(splited, currentLine, boost::is_any_of(":"));
		int key = stoi(splited[0]) - 1;
		string value = splited[1];
		mVertexes.insert(std::pair<int, string>(key, value));
	}
}

void Graph::FindAndSavePath(size_t start, size_t end, std::string & output)
{
	std::vector<std::vector<int>> paths;
	std::vector<int> path;
	DFS(path, start, end, paths);
	if (paths.size() != 0)
	{
		auto bySize = [](const std::vector<int> & i, const std::vector<int> & j)
		{
			return (i.size() < j.size());
		};
		sort(paths.begin(), paths.end(), bySize);
		GenerateReport(paths, output);
		cout << "ќтчет успешно сгенерирован!";
	}
	else
	{
		cout << "ѕуть не существует" << endl;
	}
}

void Graph::GenerateReport(std::vector<std::vector<int>> &paths, std::string & output)
{
	ofstream out(output, std::ios_base::trunc);
	for (size_t i = 0; i < paths.size(); i++)
	{
		out << "--------" << endl;
		out << "÷епочка : " << i << endl;
		for (size_t j = 1; j < paths[i].size(); j++){
			out << endl;
			out << "«вено : " << j << endl;
			out << paths[i][j - 1];
			out << " ";
			out << mVertexes.at(paths[i][j - 1]);
			out << " -> ";
			out << paths[i][j];
			out << " ";
			out << mVertexes.at(paths[i][j]);
			out << endl;
			out << endl;
			out << "Ёффекты :" << endl;
			Cell * cell = mMatrix[paths[i][j - 1] - 1][paths[i][j] - 1];
			for_each(cell->mPhysPhen.begin(), cell->mPhysPhen.end(), [&](string * eff)
			{
				out << *eff << endl;
			});
		}
	}
	out.close();
}

void Graph::DFS(std::vector<int> &path, size_t & start, size_t end, Paths &paths)
{
	path.push_back(start + 1);
	mVisitedVert[start] = true;
	for (size_t r = 0; r < mMatrix.size(); r++){
		Cell * cell = mMatrix[start][r];
		if ((cell->isLinked) && (!mVisitedVert[r])){
			if (r == end)
			{
				path.push_back(end + 1);
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

void Graph::Fill(const std::string & physEffects, const std::string & physElements)
{
	ifstream in(physEffects);
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
		mVisitedVert.push_back(false);
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

