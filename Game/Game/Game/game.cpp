
#include "map.h"
#include "game.h"


void ProcessEvents(sf::RenderWindow& window, Game & game) {
	Player & player = *game.player;
	sf::View & view = *game.view;
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
			view.setSize(float(event.size.width), float(event.size.height));
			view.zoom(ViewWidth / event.size.width);

		}
	}
}

void GameInit(Game& game) {
	LevelInit(game.lvl);
	Object player = game.lvl.GetObject("player");
	PlayerInit(game.player, player.rect.left, player.rect.top, game.lvl);
	ViewInit(game.view);
}

void ViewInit(sf::View *& view) {
	view = new sf::View();
	view->reset(sf::FloatRect(0, 0, ViewWidth, ViewHeight));
}

void LevelInit(Level & level) {
	//level = new Level();
	level.LoadFromFile("map.tmx");
}
void CheckCollisions(Game& game, char axis) {
	for (int i = 0; i < game.player->obj.size(); i++) {
		Player *& player = game.player;
		//sf::FloatRect & map_bounds = game.player->obj[i].rect;
		sf::FloatRect player_bounds = player->sprite.getGlobalBounds();
		//std::cout << game.lvl.GetObject("player").rect.left;
		//проходимся по объектамs
		if (player_bounds.intersects(game.player->obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (game.player->obj[i].name == "solid")//если встретили препятствие
			{
				if (player->x_accel < 0 && axis == 'x' ) {
					player->x_pos = game.player->obj[i].rect.left + game.player->obj[i].rect.width;
				}
				if (player->x_accel > 0 && axis == 'x') {
					player->x_pos = game.player->obj[i].rect.left - player_bounds.width;
				}
				if (player->y_accel < 0 && axis == 'y') {
					player->y_pos = game.player->obj[i].rect.top + game.player->obj[i].rect.height;
					player->y_accel = 0;
				}
				if (player->y_accel > 0 && axis == 'y') {
					player->y_pos = game.player->obj[i].rect.top - player_bounds.height;
					//std::cout << player->y_pos;
					player->y_accel = 0;
				}
			}
		}
		
	}
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

void Update(Game& game, const sf::Time& deltaTime) {
	Player* & player = game.player;
	float step = player->step * deltaTime.asSeconds();
	switch (player->state) {
	case LEFT:
		player->x_accel = -step;
		break;
	case RIGHT:
		player->x_accel = step;
		break;
	case NONE:
		break;
	}

	player->x_pos += player->x_accel;
	CheckCollisions(game, 'x');

	// Jumps

	if (player->jump && player->jump_height_counter < player->max_jump) {
		float move = step * JumpingSpeedCoef;
		player->y_accel = -move;
		player->jump_height_counter += move;
	}
	else {
		player->jump = false;
		player->jump_height_counter = 0.f;
		
	}
	
	// Gravity

	if (!player->jump) {
	player->y_accel = step * FallingSpeedCoef;
	}

	player->y_pos += player->y_accel;
	CheckCollisions(game, 'y');


	player->sprite.setPosition(player->x_pos, player->y_pos);


	GetPlayerCoordinateForView(*game.view, game.player->x_pos + 30, game.player->y_pos + 45);
}

void Render(sf::RenderWindow & window, Game & game) {
	game.lvl.Draw(window);
	window.setView(*game.view);
	window.draw(game.player->sprite);
	//window.setVerticalSyncEnabled(true);
	window.display();
}





