#include "game.h"
#include <iostream>

using namespace sf;

void ProcessEvents(RenderWindow& window, Game & game) {
	Player & player = *game.player;
	View & view = *game.view;
	Event event;

	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			player.jump = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			player.state = LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			player.state = RIGHT;
		}
		else {
			player.state = NONE;
		}
		if (event.type == Event::Closed) {
			window.close();
		}
		else if (event.type == Event::Resized) {
			view.setSize(event.size.width, event.size.height);
			view.zoom(ViewWidth / event.size.width);

		}
	}
}

void GameInit(Game& game) {
	PlayerInit(game.player, 45, 0);
	MapInit(game.map);
	ViewInit(game.view);
}

void ViewInit(View *& view) {
	view = new View();
	view->reset(FloatRect(0, 0, ViewWidth, ViewHeight));
}

void CheckCollisions(Game& game) {
	Cell* cell = game.map->cells;
	Player* player = game.player;
	FloatRect player_bounds = game.player->sprite.getGlobalBounds();

	for (size_t i = 0; i < MapHeight * MapWidth; i++) {
		FloatRect map_bounds = cell[i].sprite.getGlobalBounds();

		if (cell[i].type == FREE_SPACE) {
			continue;
		}

		if (player_bounds.intersects(map_bounds)) {
			Vector2f position = player->sprite.getPosition();
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
				}
				else if (bottom_collision_size < map_bounds.height / 4.f) { // Always check bottom collision 
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


void GetPlayerCoordinateForView(View& view, float x, float y) {
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

void Update(Game& game, const Time& deltaTime) {
	Player* & player = game.player;
	float step = player->step * deltaTime.asSeconds();
	Vector2f movement = player->sprite.getPosition();
	switch (player->state) {
	case LEFT:
		movement.x -= step;
		break;
	case RIGHT:
		movement.x += step;
		break;
	case NONE:
		break;
	}

	// Jump

	if (player->jump && player->jump_height_counter < player->max_jump) {
		float move = step * JumpingSpeedCoef;
		movement.y -= move;
		player->jump_height_counter += move;

	}
	else {
		player->jump = false;
		player->jump_height_counter = 0.f;
	}

	// Gravity

	if (movement.y < GroundY && !player->jump) {
		movement.y += step * FallingSpeedCoef;
	}
	if (movement.y > GroundY) {
		movement.y = GroundY;
	}

	player->sprite.setPosition(movement);
	player->x_pos = player->sprite.getPosition().x;
	player->y_pos = player->sprite.getPosition().y;
	CheckCollisions(game);
	GetPlayerCoordinateForView(*game.view, game.player->x_pos + 30, game.player->y_pos + 45);
}

void Render(RenderWindow & window, Game & game) {
	MapDraw(window, *game.map);
	window.setView(*game.view);
	window.draw(game.player->sprite);
	window.setVerticalSyncEnabled(true);
	window.display();
}
