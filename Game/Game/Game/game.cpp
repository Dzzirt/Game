#include "game.h"
#include <iostream>

void ProcessEvents(sf::RenderWindow& window, Player& player, sf::View& view) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			player.jump = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player.state = LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player.state = RIGHT;
		}
		else {
			player.state = NONE;
		}
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		else if (event.type == sf::Event::Resized) {
			view.setSize(event.size.width, event.size.height);
			view.zoom(ViewWidth / event.size.width);

		}
	}
}

void GameInit(Game& game) {
	game.player = new Player();
	PlayerInit(*game.player, 45, 0);
	game.map = new Map();
	MapInit(*game.map);
}

void CheckCollisions(Game& game) {
	Cell* cell = game.map->cells;
	Player* player = game.player;
	sf::FloatRect player_bounds = game.player->sprite.getGlobalBounds();

	for (size_t i = 0; i < MapHeight * MapWidth; i++) {
		sf::FloatRect map_bounds = cell[i].sprite.getGlobalBounds();

		if (cell[i].type == FREE_SPACE) {
			continue;
		}

		if (player_bounds.intersects(map_bounds)) {
			sf::Vector2f position = player->sprite.getPosition();
			if (cell[i].type == BORDER) {
				if (player->state == LEFT) {
					position.x += map_bounds.left + map_bounds.width - player_bounds.left;
					player->state = NONE;
				}
				else if (player->state == RIGHT) {
					position.x -= player_bounds.left + player_bounds.width - map_bounds.left;
					player->state = NONE;
				}

			}

			if (cell[i].type == BLOCK) {
				float upper_collision_size = player_bounds.top + player_bounds.height - map_bounds.top;
				float bottom_collision_size = map_bounds.top + map_bounds.height - player_bounds.top;
				bool upper_collision = false;
				bool bottom_collision = false;

				if (upper_collision_size < map_bounds.height / 4.f) { // Always check upper collision 
					position.y = map_bounds.top - player_bounds.height;
					upper_collision = true;
				}else
				if (bottom_collision_size < map_bounds.height / 4.f) { // Always check bottom collision 
					bottom_collision = true;
					position.y = map_bounds.top + map_bounds.height;
					player->jump = false;
				}
				if (player->state == LEFT && !upper_collision && !bottom_collision) { // Check collision with left side 
					position.x += map_bounds.left + map_bounds.width - player_bounds.left;
					player->state = NONE;
				}
				else if (player->state == RIGHT && !upper_collision && !bottom_collision) { // Check collision with right side
					position.x -= player_bounds.left + player_bounds.width - map_bounds.left;
					player->state = NONE;
				}
			}
			player->sprite.setPosition(position);
			player->x_pos = player->sprite.getPosition().x;
			player->y_pos = player->sprite.getPosition().y;
		}
	}
}
