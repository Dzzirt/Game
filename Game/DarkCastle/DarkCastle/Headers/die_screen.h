#pragma once
#include "SFML/Graphics.hpp"

struct DieScreen {
	sf::Sprite sprite;
	sf::Texture texture;
};

DieScreen* CreateDieScreen();

void DieScreenInit(DieScreen & screen);

void DrawDieScreen(DieScreen & screen, sf::RenderWindow & window);

void DestroyDieScreen(DieScreen *& die_screen);