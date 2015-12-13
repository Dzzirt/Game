#pragma once
#include "SFML/Graphics.hpp"
#include "consts_and_enums.h"
#include "../Headers/resourses.h"


struct BonusLogic {
	float max_distance;
	float current_distance;
	float speed;
	int value;
	int duration;
	bool picked_up;
	sf::FloatRect* rect;
	BonusType bonus_type;
};

BonusLogic* CreateBonusLogic(BonusType type, Resourses & res, int number);

void BonusLogicInit(BonusLogic & bonus_logic, Resourses & res, BonusType type, int number);

sf::FloatRect GetBonusRectFromLvl(Level& lvl, BonusType type, int number);

void DestroyBonusLogic(BonusLogic & bonus_logic);