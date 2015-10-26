#pragma once
#include <SFML/Graphics.hpp>
#include "hp_bar.h"
#include "entity_consts.h"

const float ViewWidth = 800.f;
const float ViewHeight = 600.f;
const int XPlayerSize = 60;
const int YPlayerSize = 90;
const float TickPerFrame = 3.f;
const int ValueOfDivision = 10;

const float WhiteWeaponDamage = 15.f; 
const float GreenWeaponDamage = 30.f;
const float RedWeaponDamage = 45.f;

struct Player {
	float health_points;
	float max_health_points;
	float damage;
	bool is_attack = false;
	bool left_attack = false;
	bool right_attack = false;
	sf::View* view;
	HpBar* hp_bar;
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
	bool attack_occured = false;
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



 


void GetPlayerCoordinateForView(sf::View& view, float x, float y);

void GravityAnimation(Player& player);

void JumpAnimation(Player& player, float game_step);

void AttackAnimation(Player& player, float game_step);

void MoveAndStayAnimation(Player& player, float game_step);

void PlayerAnimations(Player& player, const sf::Time& deltaTime);

