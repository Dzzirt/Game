#include "../Headers/bonus.h"
#include "../Headers/safe_delete.h"


Bonus* CreateBonus(Resourses & res, BonusType type, int number) {
	Bonus* bonus = new Bonus();
	BonusInit(*bonus, res, type, number);
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

void BonusInit(Bonus& bonus, Resourses & res, BonusType type, int number) {
	bonus.bonus_visual = CreateBonusVisual(type, *res.int_rects);
	bonus.bonus_logic = CreateBonusLogic(type, res, number);
	bonus.bonus_visual->sprite.setPosition(bonus.bonus_logic->rect->left, bonus.bonus_logic->rect->top);
}

void DestroyBonus(Bonus *& bonus) {
	DestroyBonusVisual(bonus->bonus_visual);
	DestroyBonusLogic(bonus->bonus_logic);
	SafeDelete(bonus);
}

void BonusUpdate(Bonus & bonus, const sf::Time& deltaTime) {
	float & speed = bonus.bonus_logic->speed;
	const float & max_distance = bonus.bonus_logic->max_distance;
	float & cur_distance = bonus.bonus_logic->current_distance;
	float step = 0.f;
	if (cur_distance <= max_distance) {
		step = speed * deltaTime.asSeconds();
	}
	else {
		cur_distance = 0.f;
		speed = -speed;
	}
	cur_distance += abs(step);
	bonus.bonus_visual->sprite.move(0, step);
}