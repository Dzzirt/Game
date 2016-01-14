#pragma once
#include "hp_bar.h"


const float CPlayerDamage = 15.f;
const float BPlayerDamage = 30.f;
const float APlayerDamage = 45.f;

const float CSpearmanDamage = 10.f;
const float CJellyDamage = 5.f;
const float CJellyBossDamage = 20.f;
const float BEnemyDamage = 20.f;
const float AEnemyDamage = 30.f;

struct FightLogic {
	float health_points;
	float max_health_points;
	float damage;
	float stored_damage;
	bool attack_occured;
	bool is_dead;
};

FightLogic* CreateFightLogic(Type type);

void FightLogicInit(FightLogic& fight, Type type);

void DestroyFightLogic(FightLogic *& fight);