#include "player.h"

using namespace sf;

void PlayerInit(Player *& player, float x, float y) {
	player = new Player();
	player->x_pos = x;
	player->y_pos = y;
	player->image.loadFromFile("images/hero.png");
	player->texture.loadFromImage(player->image);
	player->sprite.setTexture(player->texture);
	player->sprite.setTextureRect(IntRect(0, 0, XPlayerSize, YPlayerSize));
	player->sprite.setPosition(x, y);
	player->max_jump = player->sprite.getGlobalBounds().height / 2;
}


