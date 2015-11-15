#pragma once

#include <list>
#include "player.h"
#include "enemy.h"




struct Game {
	Player* player;
	Level *lvl;
	std::list<Enemy*> * enemy_list;
	sf::RenderWindow * window;

};

void GameInit(Game& game);

void LevelInit(Level & level);

void ProcessEvents(sf::RenderWindow& window, Game & game);

void ProcessEnemiesEvents(Game & game);

void Update(Game& game, const sf::Time& deltaTime);

void Render(sf::RenderWindow & window, Game & game);

void CheckCollisions(Game & game);

void PlayerEnemyCollision(const Player & player, Enemy & enemy);

void EnemyPlayerCollision(const Enemy& enemy, Player& player);

void EnemyListInit(std::list<Enemy*> *& enemy_list);

