#include "../Headers/bonus_list_utils.h"
#include "../Headers/safe_delete.h"

using namespace std;
using namespace sf;

void BonusListInit(list<Bonus*>& bonus_list, Resourses& res, BonusType type)
{
	int bonuses_count = GetBonusesCount(*res.lvl, type);
	for (int i = 0; i < bonuses_count; i++)
	{
		Bonus* bonus = CreateBonus(res, type, i);
		bonus_list.push_back(bonus);
	}
}

std::list<Bonus*>* CreateBonusList(Resourses& res)
{
	auto list = new std::list<Bonus*>();
	BonusListInit(*list, res, HP_REGEN);
	BonusListInit(*list, res, ATK_UP);
	BonusListInit(*list, res, SPEED_UP);
	return list;
}

void BonusListUpdate(std::list<Bonus*> & bonuses, const Time& deltaTime)
{
	for (Bonus * bonus : bonuses)
	{
		BonusUpdate(*bonus, deltaTime);
	}
}

void DrawBonuses(std::list<Bonus*> & bonus_list, RenderWindow &window)
{
	for (list<Bonus*>::iterator iter = bonus_list.begin(); iter != bonus_list.end(); ++iter)
	{
		Bonus* bonus = *iter;
		window.draw(bonus->bonus_visual->sprite);
	}
}

void DestroyBonusList(std::list<Bonus*>*& bonus_list)
{
	for_each(bonus_list->begin(), bonus_list->end(), DestroyBonus);
	SafeDelete(bonus_list);
}