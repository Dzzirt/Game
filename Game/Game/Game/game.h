#pragma once
#include "player.h"
#include "enemy.h"
#include <list>



struct Game {
	Player* player;
	Level *lvl;
	std::list<Enemy*> * enemy_list;

};

void ProcessEvents(sf::RenderWindow& window, Game & game);

void GameInit(Game& game);

void LevelInit(Level *& level);

void Update(Game& game, const sf::Time& deltaTime);

void Render(sf::RenderWindow & window, Game & game);




