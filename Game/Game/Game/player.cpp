#include "player.h"
#include "map.h"

using namespace sf;

void PlayerUpdate(Player & player, const Time & deltaTime) {
	Vector2f movement = player.sprite.getPosition();
	switch (player.dir) {
	case LEFT:
		movement.x -= player.step * deltaTime.asSeconds();
		break;
	case RIGHT:
		movement.x += player.step * deltaTime.asSeconds();
		break;
	case JUMP:

		break;
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
	player.sprite.setTextureRect(IntRect(0, 0, 60, 90));
	player.sprite.setPosition(x, y);
}

void GetPlayerCoordinateForView(sf::View & view, float x, float y) {
	float left_right_border = view.getSize().x / 2;
	float up_down_border = view.getSize().y / 2;
	float tempX = x; float tempY = y;
	if (x < left_right_border) tempX = left_right_border;
	if (y > MapHeight * MapTextureSize - up_down_border) tempY = MapHeight * MapTextureSize - up_down_border;
	if (x > MapWidth * MapTextureSize - left_right_border) tempX = MapWidth * MapTextureSize - left_right_border;
	view.setCenter(tempX, tempY);
}