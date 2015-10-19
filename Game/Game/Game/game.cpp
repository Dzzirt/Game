#include "game.h"
#include <sstream>
#include "map.h"
using namespace sf;
using namespace std;

void EnemyUpdate(Enemy& enemy, const sf::Time& deltaTime, Game& game) {
	switch (enemy.state) {
	case LEFT:
		enemy.x_accel = -enemy.step;
		enemy.step = 200.f;
		if (!enemy.left_attack && !enemy.right_attack) {
			enemy.sprite.setTextureRect(IntRect(126, 0, -48, 84));
			enemy.displacement = 0;
		}
		break;
	case RIGHT:
		enemy.x_accel = enemy.step;
		enemy.step = 200.f;
		if (!enemy.left_attack && !enemy.right_attack) {
			enemy.sprite.setTextureRect(IntRect(78, 0, 48, 84));
			enemy.displacement = 0;
		}
		break;
	case NONE:
		break;
	}
	// Jump

	if (enemy.jump && enemy.jump_height_counter < enemy.max_jump) {
		enemy.jump_height_counter += enemy.step * deltaTime.asSeconds() * JumpingSpeedCoef;
		enemy.y_accel = -enemy.step;
	}
	else {
		enemy.jump = false;
		enemy.jump_height_counter = 0.f;
	}

	// Gravity

	if (!enemy.on_ground && !enemy.jump) {
		enemy.y_accel = 200.f;
	}

	// Attack Animation 

	if (enemy.left_attack) {
		enemy.right_attack = false;
		enemy.current_frame += float(0.05 * enemy.step * deltaTime.asSeconds());

		enemy.sprite.setTextureRect(sf::IntRect(78, 0, -78, 84));
		enemy.displacement = 30;
			enemy.step = 100.f;
		if (enemy.current_frame > 3) {
			enemy.left_attack = false;
			enemy.sprite.setTextureRect(IntRect(126, 0, -48, 84));
			enemy.displacement = 0;
			enemy.current_frame -= 3;
		}
	}

	if (enemy.right_attack) {
		enemy.left_attack = false;
		enemy.current_frame += float(0.05 * enemy.step * deltaTime.asSeconds());

		enemy.sprite.setTextureRect(sf::IntRect(0, 0, 78, 84));
		enemy.step = 100.f;
		if (enemy.current_frame > 3) {
			enemy.right_attack = false;
			enemy.sprite.setTextureRect(IntRect(78, 0, 48, 84));
			enemy.current_frame -= 3;
		}
	}


	float delta_x = enemy.x_accel * deltaTime.asSeconds();
	float delta_y = enemy.y_accel * deltaTime.asSeconds();

	game.obj[0][enemy.obj_number].rect.left += delta_x;
	game.obj[0][enemy.obj_number].rect.top += delta_y;
	CheckEnemyCollisions(enemy, game);
	enemy.x_pos = game.obj[0][enemy.obj_number].rect.left - enemy.displacement;
	enemy.y_pos = game.obj[0][enemy.obj_number].rect.top;
	enemy.sprite.setPosition(enemy.x_pos, enemy.y_pos);
}

void CheckEnemyCollisions(Enemy& enemy, Game& game) {
	enemy.on_ground = false;
	for (size_t i = 0; i < game.obj[0].size(); i++) {
		sf::FloatRect& map_bounds = game.obj[0][i].rect;
		sf::FloatRect& enemy_box = game.obj[0][enemy.obj_number].rect;
		sf::FloatRect enemy_sprite = enemy.sprite.getGlobalBounds();

		if (enemy_box.intersects(map_bounds))//проверяем пересечение игрока с объектом
		{

			if (game.obj[0][i].name == "solid") {
				bool upper_collision = false;
				bool bottom_collision = false;
				bool enemy_higher_than_object = enemy_box.top + enemy_box.height - 4 < map_bounds.top;
				bool enemy_less_than_object = enemy_box.top + 4 > map_bounds.top + map_bounds.height;

				if (enemy.y_accel > 0 && enemy_higher_than_object) { // Check upper collision 
					enemy.on_ground = true;
					enemy_box.top = map_bounds.top - enemy_box.height;
					upper_collision = true;
				}
				else if (enemy.y_accel < 0 && enemy_less_than_object) { // Check bottom collision 
					enemy_box.top = map_bounds.top + map_bounds.height;
					bottom_collision = true;
					enemy.jump = false;
				}

				if (enemy.x_accel < 0 && !upper_collision && !bottom_collision) { // Check collision with left side 

					enemy_box.left = map_bounds.left + map_bounds.width;
					if (enemy_box.top + enemy_box.height - enemy.max_jump < map_bounds.top && enemy.on_ground) {
						enemy.jump = true;
					}
				}
				else if (enemy.x_accel > 0 && !upper_collision && !bottom_collision) { // Check collision with right side

					enemy_box.left -= enemy_box.left + enemy_box.width - map_bounds.left;
					if (enemy_box.top + enemy_box.height - enemy.max_jump < map_bounds.top && enemy.on_ground) {
						enemy.jump = true;
					}
				}
			}
		}
		if (enemy_sprite.intersects(map_bounds)) {

			if (game.obj[0][i].name == "player") {

				// Доделать
			}
		}
	}
	enemy.x_accel = 0;
	enemy.y_accel = 0;
}

void PlayerUpdate(Player& player, const sf::Time& deltaTime, Game& game) {
	switch (player.state) {
	case LEFT:
		player.x_accel = -player.step;
		player.step = 200.f;
		if (!player.left_attack && !player.right_attack) {
			player.sprite.setTextureRect(IntRect(126, 0, -48, 84));
			player.displacement = 0;
		}

		break;
	case RIGHT:
		player.x_accel = player.step;
		player.step = 200.f;
		if (!player.left_attack && !player.right_attack) {
			player.sprite.setTextureRect(IntRect(78, 0, 48, 84));
			player.displacement = 0;
		}
		break;
	case NONE:
		break;
	}

	// Jump
	if (player.is_jump && player.on_ground) {
		player.jump = true;
		player.is_jump = false;
	}
	if (player.jump && player.jump_height_counter < player.max_jump) {
		player.jump_height_counter += player.step * deltaTime.asSeconds() * JumpingSpeedCoef;
		player.y_accel = -player.step;
	}
	else {
		player.jump = false;
		player.jump_height_counter = 0;
	}

	// Gravity

	if (!player.on_ground && !player.jump) {
		player.y_accel = 200.f;
	}
	 
	// Attack Animation 

	if (player.left_attack) {
		player.right_attack = false;
		player.current_frame += float(0.05 * player.step * deltaTime.asSeconds());

		player.sprite.setTextureRect(sf::IntRect(78, 0, -78, 84));
		player.displacement = 30;
		player.step = 100.f;
		if (player.current_frame > 3) {
			player.left_attack = false;
			player.sprite.setTextureRect(IntRect(126, 0, -48, 84));
			player.displacement = 0;
			player.current_frame -= 3;
		}
	}

	if (player.right_attack) {
		player.left_attack = false;
		player.current_frame += float(0.05 * player.step * deltaTime.asSeconds());

		player.sprite.setTextureRect(sf::IntRect(0, 0, 78, 84));
		player.step = 100.f;
		if (player.current_frame > 3) {
			player.right_attack = false;
			player.sprite.setTextureRect(IntRect(78, 0, 48, 84));
			player.current_frame -= 3;
		}
	}

	// Box & Sprite steps

	float delta_x = player.x_accel * deltaTime.asSeconds();
	float delta_y = player.y_accel * deltaTime.asSeconds();

	game.obj[0][player.obj_number].rect.left += delta_x;
	game.obj[0][player.obj_number].rect.top += delta_y;

	CheckPlayerCollisions(player, game);
	player.x_pos = game.obj[0][player.obj_number].rect.left - player.displacement;
	player.y_pos = game.obj[0][player.obj_number].rect.top;

	player.sprite.setPosition(player.x_pos, player.y_pos);
	GetPlayerCoordinateForView(*player.view, player.x_pos + 24 + player.displacement, player.y_pos + 42);
}

void CheckPlayerCollisions(Player& player, Game& game) {
	player.on_ground = false;
	for (size_t i = 0; i < game.obj[0].size(); i++) {
		FloatRect& map_bounds = game.obj[0][i].rect;
		FloatRect& player_box = game.obj[0][player.obj_number].rect;
		FloatRect player_sprite = player.sprite.getGlobalBounds();
		if (player_box.intersects(map_bounds)) {
			if (game.obj[0][i].name == "solid") {

				bool upper_collision = false;
				bool bottom_collision = false;
				bool player_higher_than_object = player_box.top + player_box.height - 10 < map_bounds.top;
				bool player_less_than_object = player_box.top + 10 > map_bounds.top + map_bounds.height;

				if (player.y_accel > 0 && player_higher_than_object) { // Check upper collision 
					player.on_ground = true;
					player_box.top = map_bounds.top - player_box.height;
					upper_collision = true;

				}
				else if (player.y_accel < 0 && player_less_than_object) { // Check bottom collision 
					player_box.top = map_bounds.top + map_bounds.height;
					bottom_collision = true;
					player.jump = false;
				}
				if (player.x_accel < 0 && !upper_collision && !bottom_collision) { // Check collision with left side 
					player_box.left = map_bounds.left + map_bounds.width;
				}
				else if (player.x_accel > 0 && !upper_collision && !bottom_collision) { // Check collision with right side
					player_box.left -= player_box.left + player_box.width - map_bounds.left;
				}
			}

		}
		if (player_sprite.intersects(map_bounds) && (player.left_attack || player.right_attack)) {
			if (game.obj[0][i].name.substr(0, 5) == "enemy") {
				for (std::list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
					Enemy* enemy = *iter;
					if (enemy->name == game.obj[0][i].name) {
						player.left_attack = false;
						player.right_attack = false;
						delete *iter;
						game.enemy_list->remove(*iter);
						game.obj[0].erase(game.obj[0].begin() + i);
						break;
					}
				}
				for (std::list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
					Enemy* enemy = *iter;
					if (enemy->obj_number > i) {
						enemy->obj_number--;
					}
					
				}
			}
		}
	}
	player.x_accel = 0;
	player.y_accel = 0;
}

void LevelInit(Level*& level) {
	level = new Level();
	level->LoadFromFile("map.tmx");
}

void EnemyAdd(Game& game) { // Будет несколько вариков мобов
	Enemy* enemy = new Enemy();
	stringstream number;
	number << game.enemy_list->size();
	enemy->name = "enemy" + number.str();
	char obj_number = 1;
	while (game.obj[0][obj_number].name != enemy->name) {
		obj_number++;
	}
	enemy->field_of_view = 300.f;
	enemy->obj_number = obj_number;
	enemy->state = NONE;
	enemy->x_accel = 0;
	enemy->y_accel = 0;
	enemy->image.loadFromFile("enemy_spritesheet.png");
	enemy->image.createMaskFromColor(Color(255, 255, 255));
	enemy->texture.loadFromImage(enemy->image);
	enemy->sprite.setTexture(enemy->texture);
	enemy->sprite.setTextureRect(sf::IntRect(78, 0, XEnemySize, YEnemySize));
	enemy->max_jump = 90.f;
	game.enemy_list->push_back(enemy);

}

void PlayerInit(Game& game) {
	game.player = new Player();
	char obj_number = 1;
	while (game.obj[0][obj_number].name != "player") {
		obj_number++;
	}
	game.player->obj_number = obj_number;
	game.player->x_accel = 0;
	game.player->y_accel = 0;
	game.player->image.loadFromFile("hero_spritesheet.png");
	game.player->texture.loadFromImage(game.player->image);
	game.player->sprite.setTexture(game.player->texture);
	game.player->sprite.setTextureRect(IntRect(78, 0, 48, 84));
	game.player->max_jump = 100.f;
}

void EnemyListInit(list<Enemy*>*& enemy_list) {
	enemy_list = new list<Enemy*>();
}

void ObjectsInit(vector<Object>*& obj, Level* level) {
	obj = new vector<Object>();
	*obj = level->GetAllObjects();
}


void GameInit(Game& game) {
	LevelInit(game.lvl);
	ObjectsInit(game.obj, game.lvl);
	PlayerInit(game);
	ViewInit(game.player->view);
	EnemyListInit(game.enemy_list);
	int enemies = game.lvl->GetAllObjects().size() - game.lvl->GetObjects("solid").size() - 1;
	cout << enemies << endl;
	for (int i = 0; i < enemies; i++) {
		EnemyAdd(game);
	}
}

void ProcessEnemiesEvents(Game& game) {
	FloatRect player_box = game.obj[0][game.player->obj_number].rect;
	float player_box_right = player_box.left + player_box.width;
	for (std::list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
		Enemy* enemy = *iter;
		FloatRect enemy_box = game.obj[0][enemy->obj_number].rect;
		float enemy_box_right = enemy_box.left + enemy_box.width;
		bool right_detect = player_box.left - enemy->field_of_view <= enemy_box_right && player_box.left >= enemy_box.left;
		bool left_detect = player_box_right + enemy->field_of_view >= enemy_box.left && player_box.left <= enemy_box.left;
		bool up_keep_detection = player_box.top + player_box.height >= enemy_box.top - player_box.height;
		if (enemy->enemy_state == NOT_DETECT) {
			if (left_detect || right_detect && up_keep_detection) {
				enemy->enemy_state = DETECT;
			}
		}
		else if (enemy->enemy_state == DETECT) {
			if (left_detect) {
				enemy->state = LEFT;
			}
			else if (right_detect) {
				enemy->state = RIGHT;
			}
			else enemy->state = NONE;
			bool close_from_left = enemy_box_right > player_box.left - 20 && enemy_box_right < player_box_right;
			bool close_from_right = enemy_box.left < player_box_right + 20 && enemy_box.left > player_box.left;
			if (close_from_left) {
				enemy->right_attack = true;
				enemy->state = NONE;
			}else if (close_from_right) {
				enemy->left_attack = true;
				enemy->state = NONE;
			}
		}

	}
}

void ProcessEvents(sf::RenderWindow& window, Game& game) {
	ProcessEnemiesEvents(game);
	ProcessPlayerEvents(window, game);
}

void ProcessPlayerEvents(sf::RenderWindow& window, Game& game) {
	Player& player = *game.player;
	sf::View& view = *game.player->view;
	sf::Event event;

	while (window.pollEvent(event)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			player.is_jump = true;
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			const float mouse_global_x = sf::Mouse::getPosition(window).x + game.player->view->getCenter().x - (window.getSize().x / 2);
			if (mouse_global_x > game.obj[0][player.obj_number].rect.left + 24) {
				player.right_attack = true;

			}
			if (mouse_global_x < game.obj[0][player.obj_number].rect.left + 24) {
				player.left_attack = true;

			}

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

void Update(Game& game, const sf::Time& deltaTime) {
	PlayerUpdate(*game.player, deltaTime, game);
	for (list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
		Enemy* enemy = *iter;
		EnemyUpdate(*enemy, deltaTime, game);
	}
}

void Render(sf::RenderWindow& window, Game& game) {
	game.lvl->Draw(window);
	window.setView(*game.player->view);
	window.draw(game.player->sprite);
	for (list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
		Enemy* enemy = *iter;
		window.draw(enemy->sprite);
	}
	window.display();
}
