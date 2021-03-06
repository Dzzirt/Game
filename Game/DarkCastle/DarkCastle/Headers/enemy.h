#pragma once


#include <SFML/Graphics.hpp>
#include "level.hpp"
#include "movement.h"
#include "fight_logic.h"
#include "visual.h"
#include "logic_AI.h"
#include "resourses.h"


struct Enemy {
	Movement * movement;
	FightLogic * fight;
	HpBar* hp_bar;
	Visual * visual;
	LogicAI * ai;
	Type type;
	bool is_attacked;
	bool is_injured;
};


Enemy* CreateEnemy(Resourses & res, int number, Type type);

void EnemyInit(Enemy& enemy, Type type, Resourses & res, int number);

sf::FloatRect GetEnemyRectFromLvl(Level & lvl, Type type, int number);

int GetEnemiesCount(Level & lvl, Type type);

void ProcessCollision(Enemy & enemy, const Object & map_object);

void ProcessEnemyEvents(Enemy& enemy, sf::FloatRect & player_box);

void EnemyUpdate(Enemy& enemy, const sf::Time& deltaTime, Level& level, sf::View & view);

void AnimationsUpdate(Enemy& enemy);

void CheckEnemyAndLevelCollision(Enemy & enemy, Level & level);

void DestroyEnemy(Enemy *& enemy);

