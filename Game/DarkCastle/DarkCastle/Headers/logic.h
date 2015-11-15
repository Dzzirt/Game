#pragma once
#include "fight_logic.h"
#include "movement.h"


struct Logic {
	Movement * movement;

	FightLogic * fight;
};

void LogicInit(Logic & logic, Type type);