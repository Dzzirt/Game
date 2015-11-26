#include "../Headers/bonus.h"


Bonus* CreateBonus(Level & level, BonusType type, int number) {
	Bonus* bonus = new Bonus();
	BonusInit(*bonus, level, type, number);
	return bonus;
}

int GetBonusesCount(Level& lvl, BonusType type) {
	switch (type) {
	case HP_REGEN:
		return lvl.GetMatchObjects(0, 8, "HP_REGEN").size();
	case ATK_UP:
		return lvl.GetMatchObjects(0, 6, "ATK_UP").size();
	case SPEED_UP:
		return lvl.GetMatchObjects(0, 8, "SPEED_UP").size();
	}
	return 0;
}

void BonusInit(Bonus& bonus, Level & level, BonusType type, int number) {
	bonus.bonus_visual = CreateBonusVisual(type);
	bonus.value = GetBonusValue(type, "bonus_config.txt");
	bonus.rect = new sf::Rect<float>;
	*bonus.rect = GetBonusRectFromLvl(level, type, number);
}


sf::FloatRect GetBonusRectFromLvl(Level& lvl, BonusType type, int number) {
	std::stringstream str_number;
	std::string bonus_type = TypeToString(type);
	str_number << number;
	return lvl.GetObject(bonus_type + str_number.str()).rect;
}

void DestroyBonus(Bonus& bonus) {
	DestroyBonusVisual(*bonus.bonus_visual);
	delete &bonus;
}