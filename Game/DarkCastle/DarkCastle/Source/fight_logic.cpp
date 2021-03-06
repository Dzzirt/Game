#include "../Headers/consts_and_enums.h"
#include "../Headers/fight_logic.h"
#include "../Headers/safe_delete.h"


FightLogic* CreateFightLogic(Type type) {
	FightLogic * fight = new FightLogic();
	FightLogicInit(*fight, type);
	return fight;
}

void FightLogicInit(FightLogic& fight, Type type) {
	switch (type) {
		case PLAYER:
			fight.health_points = 100.f;
			fight.max_health_points = 100.f;
			fight.damage = CPlayerDamage;
			break;
		case SPEARMAN:
			fight.health_points = 50.f;
			fight.max_health_points = 50.f;
			fight.damage = CSpearmanDamage;
			break;
		case JELLY_BOSS:
			fight.health_points = 150.f;
			fight.max_health_points = 150.f;
			fight.damage = CJellyBossDamage;
			break;
		case JELLY:
			fight.health_points = 70.f;
			fight.max_health_points = 70.f;
			fight.damage = CJellyDamage;
			break;
		default: break;
	}
	fight.stored_damage = fight.damage;
	fight.attack_occured = false;
	fight.is_dead = false;
}

void DestroyFightLogic(FightLogic *& fight) {
	SafeDelete(fight);
}