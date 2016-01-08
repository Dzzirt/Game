#include "../Headers/duration_vec_utils.h"
#include "../Headers/safe_delete.h"

using namespace std;
using namespace sf;

std::list<DurationController*>* CreateDurationControllerVec()
{
	std::list<DurationController*>* controllers = new std::list<DurationController*>();
	return controllers;
}

void DestroyDurationControllerVec(std::list<DurationController*> *& dur_ctrl_vec)
{
	if (dur_ctrl_vec)
	{
		for (DurationController* ctrl : *dur_ctrl_vec)
		{
			DestroyDurationController(ctrl);
		}
		SafeDelete(dur_ctrl_vec);
	}

}

void DurationControllersVecUpdate(std::list<DurationController*> & ctrls, const Time& deltaTime)
{
	for (DurationController *& ctrl : ctrls)
	{
		DuratonControllerUpdate(*ctrl, deltaTime);
	}
}