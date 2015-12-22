#include "vector"
#include <algorithm> 

struct Cell
{
	std::vector<std::string*> mPhysPhen;
	bool isLinked;

	Cell();
	~Cell();
	void Add(std::string & phenomen);
};