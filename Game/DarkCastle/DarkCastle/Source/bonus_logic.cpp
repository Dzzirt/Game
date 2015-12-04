#include "../Headers/bonus_logic.h"
#include "../Headers/using_json.h"

BonusLogic* CreateBonusLogic(BonusType type, Level& level, int number) {
	BonusLogic * logic = new BonusLogic();
	BonusLogicInit(*logic, level, type, number);
	return logic;
}

void BonusLogicInit(BonusLogic& bonus_logic, Level & level, BonusType type, int number) {
	bonus_logic.bonus_type = type;
	bonus_logic.rect = new sf::Rect<float>;
	*bonus_logic.rect = GetBonusRectFromLvl(level, type, number);
	bonus_logic.picked_up = false;
	bonus_logic.value = GetBonusValue(type, "bonus_config.txt");
}

sf::FloatRect GetBonusRectFromLvl(Level& lvl, BonusType type, int number) {
	std::stringstream str_number;
	std::string bonus_type = TypeToString(type);
	str_number << number;
	return lvl.GetObject(bonus_type + str_number.str()).rect;
}

void DestroyBonusLogic(BonusLogic& bonus_logic) {
	delete bonus_logic.rect;
	delete &bonus_logic;
}