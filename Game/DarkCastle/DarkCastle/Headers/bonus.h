#pragma once

#include "bonus_visual.h"
#include "consts_and_enums.h"
#include "../Headers/resourses.h"


struct Bonus {
	int value;
	bool picked_up;
	sf::FloatRect* rect;
	BonusVisual* bonus_visual;
	BonusType bonus_type;
};

Bonus* CreateBonus(Resourses & res, BonusType type, int number);

void BonusInit(Bonus& bonus, Resourses & res, BonusType type, int number);

int GetBonusesCount(Level& lvl, BonusType type);

sf::FloatRect GetBonusRectFromLvl(Level& lvl, BonusType type, int number);

void DestroyBonus(Bonus & bonus);