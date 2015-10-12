#pragma once
#include "player.h"

const float ViewWidth = 800.f;
const float ViewHeight = 600.f;

struct Game {
	Player* player;
	sf::View* view;
	Level lvl;

};

void ProcessEvents(sf::RenderWindow& window, Game & game);

void GameInit(Game& game);

void CheckCollisions(Game& game, char axis);

void ViewInit(sf::View *& view);

void LevelInit(Level & level);

void Update(Game& game, const sf::Time& deltaTime);

void GetPlayerCoordinateForView(sf::View& view, float x, float y);

void Render(sf::RenderWindow & window, Game & game);




