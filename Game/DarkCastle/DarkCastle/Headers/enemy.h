#pragma once


#include <SFML/Graphics.hpp>
#include "level.hpp"
#include "movement.h"
#include "fight_logic.h"
#include "visual.h"
#include <list>
#include <vector>



enum EnemyState {
	NOT_DETECT,
	DETECT
};

struct Enemy {
	Movement * movement;
	FightLogic * fight;
	Visual * visual;
};

Enemy* CreateEnemy(Level & level, int number);

void DestroyEnemy(Enemy *& enemy);

void EnemyInit(Enemy& enemy, Type type, Level & level, int number);

sf::FloatRect GetEnemyRectFromLvl(Level & lvl, Type type, int number);

int GetEnemiesCount(Level & lvl, Type type);

void ProcessCollision(Enemy & enemy, const Object & map_object);

void EnemyUpdate(Enemy& enemy, const sf::Time& deltaTime, const Level & level);

void AnimationsUpdate(Enemy& enemy);

void CheckEnemyAndLevelCollision(Enemy & enemy, const Level & level);





