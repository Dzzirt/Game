#include "player.h"
#include "map.h"

using namespace sf;

void PlayerInit(Player *& player, float x, float y, Level & level) {
	player = new Player();
	player->x_pos = x;
	player->y_pos = y;
	player->x_accel = 0;
	player->y_accel = 0;
	player->image.loadFromFile("hero.png");
	player->texture.loadFromImage(player->image);
	player->sprite.setTexture(player->texture);
	player->sprite.setTextureRect(IntRect(0, 0, XPlayerSize, YPlayerSize));
	player->sprite.setPosition(x, y);
	player->max_jump = player->sprite.getGlobalBounds().height / 2;
	player->obj = level.GetAllObjects();
}


void ViewInit(sf::View*& view) {
	view = new sf::View();
	view->reset(sf::FloatRect(0, 0, ViewWidth, ViewHeight));
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

void CheckPlayerCollisions(Player & player) {
	for (size_t i = 0; i < player.obj.size(); i++) {
		sf::FloatRect & map_bounds = player.obj[i].rect;
		sf::FloatRect player_bounds = player.sprite.getGlobalBounds();
		//std::cout << game.lvl.GetObject("player").rect.left;
		//проходимся по объектамs

		if (player_bounds.intersects(player.obj[i].rect))//проверяем пересечение игрока с объектом
		{

			if (player.obj[i].name == "solid") {
				bool upper_collision = false;
				bool bottom_collision = false;
				bool player_higher_than_object = player_bounds.top + player_bounds.height - 4 < map_bounds.top;
				bool player_less_than_object = player_bounds.top + 4 > map_bounds.top + map_bounds.height;

				if (player.y_accel > 0 && player_higher_than_object) { // Check upper collision 
					player.y_pos = map_bounds.top - player_bounds.height;
					upper_collision = true;
				}
				else if (player.y_accel < 0 && player_less_than_object) { // Check bottom collision 
					player.y_pos = map_bounds.top + map_bounds.height;
					bottom_collision = true;
					player.jump = false;
				}

				if (player.x_accel < 0 && !upper_collision && !bottom_collision) { // Check collision with left side 
					player.x_pos = map_bounds.left + map_bounds.width;
				}
				else if (player.x_accel > 0 && !upper_collision && !bottom_collision) { // Check collision with right side
					player.x_pos -= player_bounds.left + player_bounds.width - map_bounds.left;
				}
			}
		}
	}
	player.x_accel = 0;
	player.y_accel = 0;
}

void PlayerUpdate(Player & player, const sf::Time& deltaTime) {
	switch (player.state) {
	case LEFT:
		player.x_accel = -player.step;
		break;
	case RIGHT:
		player.x_accel = player.step;
		break;
	case NONE:
		break;
	}
	// Jump

	if (player.jump && player.jump_height_counter < player.max_jump) {
		player.jump_height_counter += player.step * deltaTime.asSeconds() * JumpingSpeedCoef;
		player.y_accel = -player.step;
	}
	else {
		player.jump = false;
		player.jump_height_counter = 0.f;
	}

	// Gravity

	if (!player.on_ground && !player.jump) {
		player.y_accel = player.step;
	}
	player.x_pos += player.x_accel * deltaTime.asSeconds();
	player.y_pos += player.y_accel * deltaTime.asSeconds();
	player.sprite.setPosition(player.x_pos, player.y_pos);
	CheckPlayerCollisions(player);
	player.sprite.setPosition(player.x_pos, player.y_pos);
	GetPlayerCoordinateForView(*player.view, player.x_pos + 30, player.y_pos + 45);
}

