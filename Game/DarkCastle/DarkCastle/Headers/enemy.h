#pragma once


#include <SFML/Graphics.hpp>
#include "level.hpp"
#include "visual.h"
#include "logic.h"
#include <list>
#include <vector>


enum EnemyState {
	NOT_DETECT,
	DETECT
};
struct Enemy {
	Logic * logic;
	Visual * visual;
};

void EnemyInit(Enemy & enemy, Type type, sf::FloatRect & rect);

sf::FloatRect GetEnemyRectFromLvl(Level & lvl, Type type, int number);

int GetEnemiesCount(Level & lvl, Type type);

void ProcessCollision(Enemy & enemy, const Object & map_object);

void EnemyUpdate(Enemy& enemy, const sf::Time& deltaTime, const Level & level);

void AnimationsUpdate(Enemy& enemy);

void CheckEnemyAndLevelCollision(Enemy & enemy, const Level & level);





