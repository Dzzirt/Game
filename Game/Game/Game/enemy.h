#pragma once


#include <SFML/Graphics.hpp>
#include "entity_consts.h"
#include "hp_bar.h"

const int XEnemySize = 48;
const int YEnemySize = 84;

enum EnemyState {
	NOT_DETECT,
	DETECT
};

struct Enemy {
	float health_points;
	float max_health_points;
	float x_pos, y_pos, step = 80.f;
	float x_accel, y_accel;
	std::string name;
	HpBar * hp_bar;
	EnemyState enemy_state;
	State state;
	State prev_state;
	bool jump = false;
	bool attack_occured = false;
	float jump_height_counter = 0.f;
	float current_attack_frame = 0.f;
	float current_move_frame = 0.f;
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	float max_jump;
	float displacement;
	bool on_ground = false;
	bool is_attack = false;
	bool left_attack;
	bool right_attack;
	bool left_detect;
	bool right_detect;
	char obj_number;
	float field_of_view;
	int damage;
	

};





