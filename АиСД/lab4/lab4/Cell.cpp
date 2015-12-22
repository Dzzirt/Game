#include "Cell.h"
#include "SafeDelete.h"


Cell::Cell()
{
	isLinked = false;
}

void Cell::Add(std::string & phenomen)
{
	isLinked = true;
	std::string * phen = new std::string;
	*phen = phenomen;
	mPhysPhen.push_back(phen);
}

Cell::~Cell()
{
	for_each(mPhysPhen.begin(), mPhysPhen.end(), SafeDelete<std::string>);
}
