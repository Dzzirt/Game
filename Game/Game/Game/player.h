#pragma once
#include <SFML/Graphics.hpp>

enum Direction {
	JUMP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

struct Player {
	float x_pos, y_pos, step = 200.f;
	Direction dir;
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
};

void PlayerUpdate(Player& player, const sf::Time& deltaTime);

void PlayerInit(Player& player, float x, float y);

void GetPlayerCoordinateForView(sf::View & view, float x, float y);