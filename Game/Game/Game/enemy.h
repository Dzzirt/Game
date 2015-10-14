#pragma once


#include <SFML/Graphics.hpp>
#include "level.hpp"
#include "player.h"

const int XEnemySize = 30;
const int YEnemySize = 60;



struct Enemy {
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
};



void CheckEnemyCollisions(Enemy & enemy);

void EnemyUpdate(Enemy & enemy, const sf::Time& deltaTime);