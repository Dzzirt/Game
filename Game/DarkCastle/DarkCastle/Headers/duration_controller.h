#pragma once
#include "../Headers/cell_logic.h"

struct DurationController {
	float curr_elapsed_time;
	float max_elapsed_time;
	BonusType type;
};

DurationController* CreateDurationController(CellLogic & cell_logic);

void DurationControllerInit(DurationController& ctrl, CellLogic & cell_logic);

void DuratonControllerUpdate(DurationController & ctrl, const sf::Time& deltaTime);

void DestroyDurationController(DurationController & ctrl);