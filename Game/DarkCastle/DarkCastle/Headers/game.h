#pragma once

#include <list>
#include "player.h"
#include "enemy.h"
#include "bonus.h"


struct Game {
	Player* player;
	Level *lvl;
	std::list<Enemy*> * enemy_list;
	std::list<Bonus*> * bonus_list;
	sf::RenderWindow * window;
};


Game* CreateGame();

Level* CreateLevel();

sf::RenderWindow* CreateRenderWindow();

std::list<Enemy*>* CreateEnemyList(Level & level);

std::list<Bonus*>* CreateBonusList(Level& level);

void DestroyGame(Game*& game);

void DestroyLevel(Level*& level);

void DestroyWindow(sf::RenderWindow*& window);

void GameInit(Game& game);

void LevelInit(Level & level);

void BonusListInit(std::list<Bonus*>& bonus_list, Level& level, BonusType type);

void EnemyListInit(std::list<Enemy*> & en_list, Level & level, Type type);

void ProcessEvents(Game & game);

void ProcessEnemiesEvents(Enemy& enemy, sf::FloatRect & player_box);

void Update(Game& game, const sf::Time& deltaTime);

void Render(Game & game);

void CheckDynamicObjCollisions(Game& game);

void PlayerBonusCollision(const Player& player, Bonus& bonus);

void PlayerEnemyCollision(const Player & player, Enemy & enemy);

void EnemyPlayerCollision(const Enemy& enemy, Player& player);

