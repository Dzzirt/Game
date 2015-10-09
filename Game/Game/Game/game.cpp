#include "game.h"
#include <iostream>

void ProcessEvents(sf::RenderWindow & window, Player & player, sf::View & view) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			player.dir = JUMP;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player.dir = DOWN;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player.dir = LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player.dir = RIGHT;
		}
		else player.dir = NONE;

		if (event.type == sf::Event::Closed) {
			window.close();
		}
		else if (event.type == sf::Event::Resized) {
			view.setSize(event.size.width, event.size.height);
			view.zoom(ViewWidth / event.size.width);
			
		}
	}
}

void GameInit(Game & game) {
	game.player = new Player();
	PlayerInit(*game.player, 90, (MapHeight - 1) * MapTextureSize - 90);
	game.map = new Map();
	MapInit(*game.map);
}

void CheckCollisions(Game & game) {
	Cell * cell = game.map->cells;
	Player * player = game.player;
	sf::FloatRect player_bounds = game.player->sprite.getGlobalBounds();
	for (size_t i = 0; i < MapHeight * MapWidth; i++) {
		sf::FloatRect map_bounds  = cell[i].sprite.getGlobalBounds();
		if (cell[i].type == FREE_SPACE) {
			continue;
		}
		if (player_bounds.intersects(map_bounds)) {
			sf::Vector2f position = player->sprite.getPosition();
			switch (player->dir) {
			case LEFT:
				position.x += map_bounds.left + map_bounds.width - player_bounds.left;
				break;
			case RIGHT:
				position.x -= player_bounds.left + player_bounds.width - map_bounds.left;
				break;
			}
			player->sprite.setPosition(position);
			player->x_pos = player->sprite.getPosition().x;
			player->y_pos = player->sprite.getPosition().y;
			player->dir = NONE;
		}
	}
	
}