#pragma once

#include <list>
#include "enemy.h"
#include "player.h"
#include "level.hpp"

const float WindowWidth = 800.f;
const float WindowHeight = 600.f;
const float ForceOfGravity = 200.f;

struct Game {
	Player* player;
	Level *lvl;
	sf::RenderWindow * window;
	std::list<Enemy*> * enemy_list;
	std::vector<Object> * obj;
};

void ViewInit(Game & game);

void GameInit(Game& game);

void LevelInit(Level *& level);

void ProcessEvents(sf::RenderWindow& window, Game & game);

void ProcessEnemiesEvents(Game & game);

void ProcessPlayerEvents(sf::RenderWindow& window, Game& game);

void ObjectsInit(std::vector<Object> *& obj, Level * level);

void Update(Game& game, const sf::Time& deltaTime);

void Render(sf::RenderWindow & window, Game & game);

void PlayerInit(Game & game);

void CheckPlayerCollisions(Player & player, Game & game);

void PlayerUpdate(Player & player, const sf::Time& deltaTime, Game &game);

void CheckEnemyCollisions(Enemy & enemy, Game & game);

void EnemyUpdate(Enemy & enemy, const sf::Time& deltaTime, Game & game);

void EnemyAdd(Game & game);

void EnemyListInit(std::list<Enemy*> *& enemy_list);

