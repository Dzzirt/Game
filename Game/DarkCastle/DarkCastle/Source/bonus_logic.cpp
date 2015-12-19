#include "../Headers/bonus_logic.h"
#include "../Headers/using_json.h"
#include "../Headers/safe_delete.h"

BonusLogic* CreateBonusLogic(BonusType type, Resourses & res, int number) {
	BonusLogic * logic = new BonusLogic();
	BonusLogicInit(*logic, res, type, number);
	return logic;
}

void BonusLogicInit(BonusLogic& bonus_logic, Resourses & res, BonusType type, int number) {
	bonus_logic.max_distance = 10.f;
	bonus_logic.speed = 8.f;
	bonus_logic.bonus_type = type;
	bonus_logic.rect = new sf::Rect<float>;
	*bonus_logic.rect = GetBonusRectFromLvl(*res.lvl, type, number);
	bonus_logic.picked_up = false;
	bonus_logic.value = GetConfig(*res.config, "BONUS_VALUE", type);
	bonus_logic.duration = float(GetConfig(*res.config, "BONUS_DURATION", type));
}

sf::FloatRect GetBonusRectFromLvl(Level& lvl, BonusType type, int number) {
	std::stringstream str_number;
	std::string bonus_type = TypeToString(type);
	str_number << number;
	return lvl.GetObject(bonus_type + str_number.str()).rect;
}

void DestroyBonusLogic(BonusLogic *& bonus_logic) {
	SafeDelete(bonus_logic->rect);
	SafeDelete(bonus_logic);
}