#pragma once
#include <SFML/Graphics.hpp>
#include "level.hpp"

const float ViewWidth = 800.f;
const float ViewHeight = 600.f;
const int XPlayerSize = 60;
const int YPlayerSize = 90;

enum State {
	LEFT,
	RIGHT,
	NONE
};

struct Player {
	bool is_attack = false;
	bool is_jump = false;
	bool left_attack = false;
	bool right_attack = false;
	sf::View* view;
	float x_pos, y_pos, step = 200.f;
	float x_accel, y_accel;
	State state;
	bool jump = false;
	float displacement = 0;
	float jump_height_counter = 0.f;
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	float max_jump;
	bool on_ground = false;
	char obj_number;
};



 
void ViewInit(sf::View *& view);

void GetPlayerCoordinateForView(sf::View& view, float x, float y);

