#include "bonus.h"
#include "list"

std::list<Bonus*>* CreateBonusList(Resourses & res);
void BonusListInit(std::list<Bonus*>& bonus_list, Resourses & res, BonusType type);
void BonusListUpdate(std::list<Bonus*> & bonuses, const sf::Time& deltaTime);
void DrawBonuses(std::list<Bonus*> & bonus_list, sf::RenderWindow &window);
void DestroyBonusList(std::list<Bonus*>*& bonus_list);