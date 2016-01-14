#pragma once
#include "SFML/Graphics.hpp"

struct WinScreen
{
	sf::Sprite sprite;
	sf::Texture texture;
};

WinScreen* CreateWinScreen();

void WinScreenInit(WinScreen & screen);

void DrawWinScreen(WinScreen & screen, sf::RenderWindow & window);

void DestroyWinScreen(WinScreen *& win_screen);