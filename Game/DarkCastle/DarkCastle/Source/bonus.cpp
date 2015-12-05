#include "../Headers/bonus.h"



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

void DestroyBonus(Bonus& bonus) {
	DestroyBonusVisual(*bonus.bonus_visual);
	DestroyBonusLogic(*bonus.bonus_logic);
	delete &bonus;
}