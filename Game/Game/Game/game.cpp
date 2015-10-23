#include "game.h"
#include <sstream>
#include "map.h"
using namespace sf;
using namespace std;

void EnemyUpdate(Enemy& enemy, const sf::Time& deltaTime, Game& game) {
	switch (enemy.state) {
	case LEFT:
		enemy.prev_state = LEFT;
		enemy.x_accel = -enemy.step;
		if (!enemy.left_attack && !enemy.right_attack) {
			enemy.current_move_frame += float(0.05 * enemy.step * deltaTime.asSeconds());
			enemy.sprite.setTextureRect(IntRect(32 * int(enemy.current_move_frame), 46, 32, 48));
			if (enemy.current_move_frame > 7) {
				enemy.current_move_frame = 0;
			}
			enemy.displacement = 0;
		}
		break;
	case RIGHT:
		enemy.prev_state = RIGHT;
		enemy.x_accel = enemy.step;
		if (!enemy.left_attack && !enemy.right_attack) {
			enemy.current_move_frame += float(0.05 * enemy.step * deltaTime.asSeconds());
			enemy.sprite.setTextureRect(IntRect(32 * int(enemy.current_move_frame) + 32, 46, -32, 48));
			if (enemy.current_move_frame > 7) {
				enemy.current_move_frame = 0;
			}
			enemy.displacement = 0;
		}
		break;
	case NONE:
		if (enemy.prev_state == LEFT) {
			enemy.sprite.setTextureRect(IntRect(224, 46, 32, 48));
		}
		else {
			enemy.sprite.setTextureRect(IntRect(224 + 32, 46, -32, 48));
		}


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
		enemy.current_attack_frame += float(0.05 * enemy.step * deltaTime.asSeconds() * 2);
		enemy.sprite.setTextureRect(IntRect(64 * int(enemy.current_attack_frame), 0, 64, 46));
		enemy.displacement = -20;
		if (enemy.current_attack_frame > 7) {
			enemy.left_attack = false;
			enemy.current_attack_frame = 0;
		}
	}

	if (enemy.right_attack) {
		enemy.left_attack = false;
		enemy.current_attack_frame += float(0.05 * enemy.step * deltaTime.asSeconds() * 2);
		enemy.sprite.setTextureRect(IntRect(64 * int(enemy.current_attack_frame) + 64, 0, -64, 46));
		enemy.displacement = -20;
		if (enemy.current_attack_frame > 7) {
			enemy.right_attack = false;
			enemy.current_attack_frame = 0;
		}
	}


	float delta_x = enemy.x_accel * deltaTime.asSeconds();
	float delta_y = enemy.y_accel * deltaTime.asSeconds();

	game.obj[0][enemy.obj_number].rect.left += delta_x;
	game.obj[0][enemy.obj_number].rect.top += delta_y;
	CheckEnemyCollisions(enemy, game);
	enemy.x_pos = game.obj[0][enemy.obj_number].rect.left + enemy.displacement;
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
	float game_step = player.step * deltaTime.asSeconds();
	switch (player.state) {
	case LEFT:
		player.prev_state = LEFT;
		player.x_accel = -player.step;
		if (!player.left_attack && !player.right_attack) {
			player.current_move_frame += float(player.anim_speed * game_step);
			switch (int(player.current_move_frame)) {
			case 0:
				player.sprite.setTextureRect(IntRect(22, 0, -22, 42));
				break;
			case 1:
				player.sprite.setTextureRect(IntRect(23 + 32, 0, -32, 42));
				break;
			case 2:
				player.sprite.setTextureRect(IntRect(55 + 26, 0, -26, 42));
				break;
			case 3:
				player.sprite.setTextureRect(IntRect(81+ 20, 0, -20, 42));
				break;
			case 4:
				player.sprite.setTextureRect(IntRect(101 +23, 0, -23, 42));
				break;
			case 5:
				player.sprite.setTextureRect(IntRect(124+32, 0, -32, 42));
				break;
			case 6:
				player.sprite.setTextureRect(IntRect(156+27, 0, -27, 42));
				break;
			case 7:
				player.sprite.setTextureRect(IntRect(183+22, 0, -22, 42));
				break;
			default:
				player.current_move_frame = 0.f;
				break;
			}
		}

		break;
	case RIGHT:
		player.prev_state = RIGHT;
		player.x_accel = player.step;
		if (!player.left_attack && !player.right_attack) {
			player.current_move_frame += float(player.anim_speed * game_step);
			cout << int(player.current_move_frame) << endl;
			switch (int(player.current_move_frame)) {
			case 0:
				player.sprite.setTextureRect(IntRect(0, 0, 22, 42));
				break;
			case 1:
				player.sprite.setTextureRect(IntRect(23, 0, 32, 42));
				break;
			case 2:
				player.sprite.setTextureRect(IntRect(55, 0, 26, 42));
				break;
			case 3:
				player.sprite.setTextureRect(IntRect(81, 0, 20, 42));
				break;
			case 4:
				player.sprite.setTextureRect(IntRect(101, 0, 23, 42));
				break;
			case 5:
				player.sprite.setTextureRect(IntRect(124, 0, 32, 42));
				break;
			case 6:
				player.sprite.setTextureRect(IntRect(156, 0, 27, 42));
				break;
			case 7:
				player.sprite.setTextureRect(IntRect(183, 0, 22, 42));
				break;
			default:
				player.current_move_frame = 0.f;
				break;
			}
		}
		break;
	case NONE:
		player.current_stay_frame += float(player.anim_speed * game_step / 5);
		if (player.current_stay_frame > 2) {
			player.current_stay_frame = 0.f;
		}
		
		if (player.prev_state == RIGHT) {
			player.sprite.setTextureRect(IntRect(34 * int(player.current_stay_frame), 132, 34, 41));
		}
		else {
			player.sprite.setTextureRect(IntRect(34 * int(player.current_stay_frame) + 34, 132, -34, 41));
		}
		
		break;
	}

	// Jump
	if (player.start_jumping && player.on_ground) {
		player.in_jump = true;
		player.start_jumping = false;
	}
	if (player.jump_animation) {
		player.sprite.setTextureRect(IntRect(117, 87, 39, 45));
	}
	if (player.in_jump && player.jump_height_counter < player.max_jump) {
		player.jump_animation = true;
		player.jump_height_counter += game_step * JumpingSpeedCoef;
		player.y_accel = -player.step;
		player.current_jump_frame += float(0.07 * game_step);
		switch (int(player.current_jump_frame)) {
		case 0:
			player.sprite.setTextureRect(IntRect(0, 87, 39, 44));
			break;
		case 1:
			player.sprite.setTextureRect(IntRect(39, 87, 39, 44));
			break;
		case 2:
			player.sprite.setTextureRect(IntRect(78, 87, 39, 45));
			break;
		case 3:
			player.sprite.setTextureRect(IntRect(117, 87, 39, 45));
			break;
		default:
			break;
		}
	}
	else {
		player.in_jump = false;
		player.current_jump_frame = 0.f;
		player.jump_height_counter = 0;
	}

	// Gravity

	if (!player.on_ground && !player.in_jump) {
		player.y_accel = 200.f;
	}

	// Attack Animation 

	if (player.left_attack) {
		player.displacement = 0;
		player.right_attack = false;
		player.current_attack_frame += float(0.1 * game_step);
		switch (int(player.current_attack_frame)) {
		case 0:
			player.sprite.setTextureRect(IntRect(0 + 30, 44, -30, 44));
			break;
		case 1:
			player.sprite.setTextureRect(IntRect(30 + 24, 44, -24, 44));
			break;
		case 2:
			player.sprite.setTextureRect(IntRect(54 + 27, 44, -27, 44));
			break;
		case 3:
			player.displacement = -20;
			player.sprite.setTextureRect(IntRect(81 + 49, 44, -49, 44));
			break;
		case 4:
			player.displacement = -20;
			player.sprite.setTextureRect(IntRect(130 + 68, 44, -68, 44));
			break;
		case 5:
			player.sprite.setTextureRect(IntRect(198 + 44, 44, -44, 44));
			break;
		default:
			player.left_attack = false;
			player.current_attack_frame = 0.f;
			player.sprite.setTextureRect(IntRect(22, 0, -22, 42));
			break;
		}
	}

	if (player.right_attack) {
		player.displacement = 0;
		player.left_attack = false;
		player.current_attack_frame += float(0.1 * game_step);
		switch (int(player.current_attack_frame)) {
		case 0:
			player.sprite.setTextureRect(IntRect(0, 44, 30, 44));
			break;
		case 1:
			player.sprite.setTextureRect(IntRect(30, 44, 24, 44));
			break;
		case 2:
			player.sprite.setTextureRect(IntRect(54, 44, 27, 44));
			break;
		case 3:
			player.sprite.setTextureRect(IntRect(81, 44, 49, 44));
			break;
		case 4:
			player.displacement = -20;
			player.sprite.setTextureRect(IntRect(130, 44, 68, 44));
			break;
		case 5:
			player.displacement = -20;
			player.sprite.setTextureRect(IntRect(198, 44, 44, 44));
			break;
		default:
			player.right_attack = false;
			player.current_attack_frame = 0.f;
			player.sprite.setTextureRect(IntRect(0, 0, 22, 42));
			break;
		}
	}

	// Box & Sprite steps

	float delta_x = player.x_accel * deltaTime.asSeconds();
	float delta_y = player.y_accel * deltaTime.asSeconds();

	game.obj[0][player.obj_number].rect.left += delta_x;
	game.obj[0][player.obj_number].rect.top += delta_y;

	CheckPlayerCollisions(player, game);
	player.x_pos = game.obj[0][player.obj_number].rect.left + player.displacement;
	player.y_pos = game.obj[0][player.obj_number].rect.top + game.obj[0][player.obj_number].rect.height;
	player.sprite.setOrigin(0, 42);
	player.sprite.setPosition(player.x_pos, player.y_pos);
	GetPlayerCoordinateForView(*player.view, player.x_pos - player.displacement, player.y_pos);
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

				if (player.y_accel > 0 && player_higher_than_object) {// Check upper collision 
					player.jump_animation = false;
					player.on_ground = true;
					player_box.top = map_bounds.top - player_box.height;
					upper_collision = true;

				}
				else if (player.y_accel < 0 && player_less_than_object) { // Check bottom collision 
					player_box.top = map_bounds.top + map_bounds.height;
					bottom_collision = true;
					player.in_jump = false;
				}
				if (player.x_accel < 0 && !upper_collision && !bottom_collision) { // Check collision with left side 
					player_box.left = map_bounds.left + map_bounds.width;
				}
				else if (player.x_accel > 0 && !upper_collision && !bottom_collision) { // Check collision with right side
					player_box.left -= player_box.left + player_box.width - map_bounds.left;
				}
			}

		}
		if (player_sprite.intersects(map_bounds) && (player.left_attack || player.right_attack) && int(player.current_attack_frame) == 3) {
			if (game.obj[0][i].name.substr(0, 5) == "enemy") {
				for (std::list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
					Enemy* enemy = *iter;
					if (enemy->name == game.obj[0][i].name) {
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
	enemy->image.loadFromFile("BIGknight_enemy.png");
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
	game.player->image.loadFromFile("hero.png");
	//game.player->image.createMaskFromColor(Color(255, 255, 255));
	game.player->texture.loadFromImage(game.player->image);
	game.player->sprite.setTexture(game.player->texture);
	game.player->sprite.setTextureRect(IntRect(0, 0, 22, 42));
	game.player->max_jump = 150.f;
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
		bool not_too_higher = player_box.top + player_box.height >= enemy_box.top - player_box.height;
		if (enemy->enemy_state == NOT_DETECT) {
			if (left_detect || right_detect && not_too_higher) {
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
			bool close_from_left = enemy_box_right > player_box.left && enemy_box_right < player_box_right;
			bool close_from_right = enemy_box.left < player_box_right && enemy_box.left > player_box.left;
			if (close_from_left) {
				enemy->right_attack = true;
				enemy->left_attack = false;
				enemy->state = NONE;
			}
			else if (close_from_right) {
				enemy->left_attack = true;
				enemy->right_attack = false;
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
			player.start_jumping = true;
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
