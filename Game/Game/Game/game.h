#pragma once
#include "player.h"
#include "map.h"


const float ViewWidth = 800.f;
const float ViewHeight = 600.f;

struct Game {
	Player* player;
	Map* map;
};

void ProcessEvents(sf::RenderWindow & window, Player & player, sf::View & view);

void GameInit(Game & game);

void CheckCollisions(Game & game);
