#pragma once
#include "hp_bar.h"


const float CPlayerDamage = 15.f;
const float BPlayerDamage = 30.f;
const float APlayerDamage = 45.f;

const float CEnemyDamage = 10.f;
const float BEnemyDamage = 20.f;
const float AEnemyDamage = 30.f;

struct FightLogic {
	float health_points;
	float max_health_points;
	float damage;
	bool attack_occured;
	bool is_dead;
	HpBar* hp_bar;
};

FightLogic* CreateFightLogic(Type type);

void FightLogicInit(FightLogic& fight, Type type);

void HpBarUpdate(FightLogic & fight, sf::FloatRect rect_for_place, Type type);

void PlayerHpBarUpdate(FightLogic & fight, sf::View & view);

void DestroyFightLogic(FightLogic *& fight);