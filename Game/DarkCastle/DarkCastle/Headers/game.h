#pragma once

#include <list>
#include "player.h"
#include "enemy.h"
#include "bonus.h"
#include "resourses.h"


struct Game {
	Player* player;
	Resourses* res;
	std::list<Enemy*> * enemy_list;
	std::list<Bonus*> * bonus_list;
	sf::RenderWindow * window;
};


Game* CreateGame();



sf::RenderWindow* CreateRenderWindow();

std::list<Enemy*>* CreateEnemyList(Resourses & res);

std::list<Bonus*>* CreateBonusList(Resourses & res);

void DestroyGame(Game*& game);



void DestroyWindow(sf::RenderWindow*& window);

void GameInit(Game& game);



void BonusListInit(std::list<Bonus*>& bonus_list, Resourses & res, BonusType type);

void EnemyListInit(std::list<Enemy*> & en_list, Resourses & res, Type type);

void ProcessEvents(Game & game);

void ProcessEnemiesEvents(Enemy& enemy, sf::FloatRect & player_box);

void Update(Game& game, const sf::Time& deltaTime);

void Render(Game & game);

void CheckDynamicObjCollisions(Game& game);

void PlayerBonusCollision(const Player& player, Bonus& bonus);

void PlayerEnemyCollision(const Player & player, Enemy & enemy);

void EnemyPlayerCollision(const Enemy& enemy, Player& player);

