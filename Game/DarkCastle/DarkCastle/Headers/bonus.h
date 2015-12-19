#pragma once

#include "bonus_visual.h"
#include "bonus_logic.h"
#include "consts_and_enums.h"
#include "../Headers/resourses.h"


struct Bonus {
	BonusVisual* bonus_visual;
	BonusLogic* bonus_logic;
};

Bonus* CreateBonus(Resourses & res, BonusType type, int number);

void BonusInit(Bonus& bonus, Resourses & res, BonusType type, int number);

void BonusUpdate(Bonus & bonus, const sf::Time& deltaTime);

int GetBonusesCount(Level& lvl, BonusType type);

void DestroyBonus(Bonus *& bonus);