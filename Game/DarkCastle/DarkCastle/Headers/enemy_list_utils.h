#pragma once


std::list<Enemy*>* CreateEnemyList(Resourses & res);

void EnemyListInit(std::list<Enemy*> & en_list, Resourses & res, Type type);

void EnemyListUpdate(std::list<Enemy*> & enemy_list, Level & level, const Time& deltaTime);

void DrawEnemies(std::list<Enemy*> & enemies, sf::RenderWindow &window);