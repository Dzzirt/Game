#pragma once
#include "SFML/Graphics.hpp"
#include "consts_and_enums.h"
#include "level.hpp"


struct BonusLogic {
	int value;
	bool picked_up;
	sf::FloatRect* rect;
	BonusType bonus_type;
};

BonusLogic* CreateBonusLogic(BonusType type, Level& level, int number);

void BonusLogicInit(BonusLogic & bonus_logic, Level& level, BonusType type, int number);

sf::FloatRect GetBonusRectFromLvl(Level& lvl, BonusType type, int number);

void DestroyBonusLogic(BonusLogic & bonus_logic);