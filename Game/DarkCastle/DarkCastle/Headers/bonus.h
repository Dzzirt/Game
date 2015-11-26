#pragma once

#include "bonus_visual.h"
#include "consts_and_enums.h"
#include "../Headers/level.hpp"



struct Bonus {
	int value;
	bool picked_up;
	sf::FloatRect* rect;
	BonusVisual* bonus_visual;
	BonusType bonus_type;
};

Bonus* CreateBonus(Level & level, BonusType type, int number);

void BonusInit(Bonus& bonus, Level & level, BonusType type, int number);

int GetBonusesCount(Level& lvl, BonusType type);

sf::FloatRect GetBonusRectFromLvl(Level& lvl, BonusType type, int number);

void DestroyBonus(Bonus & bonus);

