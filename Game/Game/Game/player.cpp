#include "player.h"
#include "map.h"
#include <iostream>

using namespace sf;

void PlayerUpdate(Player& player, const Time& deltaTime) {
	float step = player.step * deltaTime.asSeconds();
	Vector2f movement = player.sprite.getPosition();
	switch (player.state) {
	case LEFT:
		movement.x -= step;
		break;
	case RIGHT:
		movement.x += step;
		break;
	}

	// Jump

	if (player.jump && player.jump_height_counter < player.max_jump) {
		float move = step * JumpingSpeedCoef;
		movement.y -= move;
		player.jump_height_counter += move;

	}
	else {
		player.jump = false;
		player.jump_height_counter = 0.f;
	}

	// Gravity

	if (movement.y < GroundY && !player.jump) {
		movement.y += step * FallingSpeedCoef;
	}
	if (movement.y > GroundY) {
		movement.y = GroundY;
	}

	player.sprite.setPosition(movement);
	player.x_pos = player.sprite.getPosition().x;
	player.y_pos = player.sprite.getPosition().y;
}

void PlayerInit(Player& player, float x, float y) {
	player.x_pos = x;
	player.y_pos = y;
	player.image.loadFromFile("images/hero.png");
	player.texture.loadFromImage(player.image);
	player.sprite.setTexture(player.texture);
	player.sprite.setTextureRect(IntRect(0, 0, XPlayerSize, YPlayerSize));
	player.sprite.setPosition(x, y);
	player.max_jump = player.sprite.getGlobalBounds().height / 2;
}

void GetPlayerCoordinateForView(sf::View& view, float x, float y) {
	float left_right_border = view.getSize().x / 2;
	float up_down_border = view.getSize().y / 2;
	float tempX = x;
	float tempY = y;

	// Left border collision
	if (x < left_right_border) tempX = left_right_border;

	// Down border collision
	if (y > MapHeight * MapTextureSize - up_down_border) tempY = MapHeight * MapTextureSize - up_down_border;

	// Right border collision
	if (x > MapWidth * MapTextureSize - left_right_border) tempX = MapWidth * MapTextureSize - left_right_border;

	// Up border collision
	if (y < up_down_border) tempY = up_down_border;

	view.setCenter(tempX, tempY);
}
