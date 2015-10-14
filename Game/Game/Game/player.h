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
	sf::View* view;
	float x_pos, y_pos, step = 200.f;
	float x_accel, y_accel;
	State state;
	bool jump = false;
	float jump_height_counter = 0.f;
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	float max_jump;
	bool on_ground = false;
	std::vector<Object> obj;
	sf::Rect<float> box;
};



void PlayerInit(Player *& player, Level & level);
 
void ViewInit(sf::View *& view);

void GetPlayerCoordinateForView(sf::View& view, float x, float y);

void CheckPlayerCollisions(Player & player);

void PlayerUpdate(Player & player, const sf::Time& deltaTime);