#pragma once


#include <SFML/Graphics.hpp>
#include "player.h"

const int XEnemySize = 48;
const int YEnemySize = 84;

enum EnemyState {
	NOT_DETECT,
	DETECT
};

struct Enemy {
	float x_pos, y_pos, step = 120.f;
	float x_accel, y_accel;
	std::string name;
	EnemyState enemy_state;
	State state;
	bool jump = false;
	float jump_height_counter = 0.f;
	float current_frame = 0.f;
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	float max_jump;
	float displacement;
	bool on_ground = false;
	bool is_attack = true;
	bool left_attack;
	bool right_attack;
	bool left_detect;
	bool right_detect;
	char obj_number;
	float field_of_view;

};





