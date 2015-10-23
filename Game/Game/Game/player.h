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
	bool left_attack = false;
	bool right_attack = false;
	sf::View* view;
	float x_pos, y_pos, step = 150.f;
	float x_accel, y_accel;
	bool jump_animation = false;
	float current_attack_frame = 0.f;
	float current_move_frame = 0.f;
	float current_jump_frame = 0.f;
	float current_stay_frame = 0.f;
	float anim_speed = 0.07;
	State state;
	State prev_state;
	bool in_jump = false;
	bool start_jumping = false;
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

