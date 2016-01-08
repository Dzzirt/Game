#include "duration_controller.h"
#include "list"

std::list<DurationController*>* CreateDurationControllerVec();
void DestroyDurationControllerVec(std::list<DurationController*> *& dur_ctrl_vec);
void DurationControllersVecUpdate(std::list<DurationController*> & ctrls, const sf::Time& deltaTime);