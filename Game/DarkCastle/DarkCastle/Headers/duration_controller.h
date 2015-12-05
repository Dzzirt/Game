#pragma once
#include "../Headers/bonus_logic.h"

struct DurationController {
	float curr_elapsed_time;
	float max_elapsed_time;
	BonusType type;
};

DurationController* CreateDurationController(BonusLogic & b_logic);

void DurationControllerInit(DurationController& ctrl, BonusLogic & b_logic);

void DuratonControllerUpdate(DurationController & ctrl, const sf::Time& deltaTime);

void DestroyDurationController(DurationController & ctrl);