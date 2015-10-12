#pragma once
#include <SFML/Graphics.hpp>
#include "level.hpp"


const int XPlayerSize = 60;
const int YPlayerSize = 90;

enum State {
	LEFT,
	RIGHT,
	NONE
};

struct Player {
	float x_pos, y_pos, step = 200.f;
	State state;
	bool jump = false;
	float jump_height_counter = 0.f;
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	float max_jump;
	std::vector<Object> obj;
};



void PlayerInit(Player *& player, float x, float y, Level & level);
 
