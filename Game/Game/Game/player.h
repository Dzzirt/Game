#pragma once
#include <SFML/Graphics.hpp>

enum State {
	LEFT,
	RIGHT,
	JUMP,
	NONE
};

struct Player {
	float x_pos, y_pos, step = 200.f;
	State state;
	bool on_ground = true;
	bool jump = false;
	bool on_block = false;
	float jump_height_counter = 0.f;
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
};

void PlayerUpdate(Player& player, const sf::Time& deltaTime);

void PlayerInit(Player& player, float x, float y);

void GetPlayerCoordinateForView(sf::View & view, float x, float y);