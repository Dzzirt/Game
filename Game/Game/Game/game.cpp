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
			enemy.current_move_frame += float(0.1 * enemy.step * deltaTime.asSeconds());
			enemy.sprite.setTextureRect(IntRect(16 * int(enemy.current_move_frame), 23, 16, 24));
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
			enemy.current_move_frame += float(0.1 * enemy.step * deltaTime.asSeconds());
			enemy.sprite.setTextureRect(IntRect(16 * int(enemy.current_move_frame) + 16, 23, -16, 24));
			if (enemy.current_move_frame > 7) {
				enemy.current_move_frame = 0;
			}
			enemy.displacement = 0;
		}
		break;
	case NONE:
		if (enemy.prev_state == LEFT) {
			enemy.sprite.setTextureRect(IntRect(112, 23, 16, 24));
		}
		else {
			enemy.sprite.setTextureRect(IntRect(112 + 15, 23, -16, 24));
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
		enemy.y_accel = ForceOfGravity;
	}

	// Attack Animation 

	if (enemy.left_attack) {
		enemy.right_attack = false;
		enemy.sprite.setTextureRect(IntRect(32 * int(enemy.current_attack_frame), 0, 32, 23));
		enemy.current_attack_frame += float(0.1 * enemy.step * deltaTime.asSeconds());
		enemy.displacement = -10;
		if (enemy.current_attack_frame > 7) {
			enemy.attack_occured = false;
			enemy.left_attack = false;
			enemy.current_attack_frame = 0.f;
		}
	}

	if (enemy.right_attack) {
		enemy.left_attack = false;
		enemy.sprite.setTextureRect(IntRect(32 * int(enemy.current_attack_frame) + 32, 0, -32, 23));
		enemy.current_attack_frame += float(0.1 * enemy.step * deltaTime.asSeconds());
		enemy.displacement = -10;
		if (enemy.current_attack_frame > 7) {
			enemy.attack_occured = false;
			enemy.right_attack = false;
			enemy.current_attack_frame = 0.f;
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

	
	enemy.hp_bar->bar_sprite.setTextureRect(IntRect(0, 0, EnemyHpBarWidth, EnemyHpBarHeight));
	FloatRect enemy_bounds = enemy.sprite.getGlobalBounds();
	enemy.hp_bar->bar_sprite.setPosition(enemy_bounds.left + (enemy_bounds.width / 2.f), enemy_bounds.top - 10.f);
	enemy.hp_bar->bar_sprite.setOrigin(enemy.hp_bar->bar_texture.getSize().x / 2.f, 0);
	float health_in_percent = enemy.health_points / enemy.max_health_points;
	enemy.hp_bar->strip_sprite.setTextureRect(IntRect(0, EnemyHpBarHeight, EnemyHpStripWidth * health_in_percent, 1));
	enemy.hp_bar->strip_sprite.setPosition(enemy.hp_bar->bar_sprite.getGlobalBounds().left + 1, enemy.hp_bar->bar_sprite.getGlobalBounds().top + 1);
}

void CheckEnemyCollisions(Enemy& enemy, Game& game) {
	enemy.on_ground = false;
	for (size_t i = 0; i < game.obj[0].size(); i++) {
		sf::FloatRect& map_bounds = game.obj[0][i].rect;
		sf::FloatRect& enemy_box = game.obj[0][enemy.obj_number].rect;
		sf::FloatRect enemy_sprite = enemy.sprite.getGlobalBounds();

		if (enemy_box.intersects(map_bounds))// Check intersect of player with object
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
		if (enemy_sprite.intersects(map_bounds) && (enemy.left_attack || enemy.right_attack) && int(enemy.current_attack_frame) == 6) {
			if (game.obj[0][i].name == "player" && enemy.attack_occured == false) {
				enemy.attack_occured = true;
				game.player->health_points -= enemy.damage;
				cout << game.player->health_points << endl;
			}
		}
	}
	enemy.x_accel = 0;
	enemy.y_accel = 0;
}

void PlayerUpdate(Player& player, const sf::Time& deltaTime, Game& game) {
	if (player.health_points <= 0) {
		game.window->close();
	}
	float game_step = player.step * deltaTime.asSeconds();
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

	// Gravity

	if (!player.in_jump) {
		player.y_accel = ForceOfGravity;
	}

	// Jump

	if (player.in_jump && player.jump_height_counter < player.max_jump) {
		// Disable attack
		player.left_attack = false;
		player.right_attack = false;
		//
		player.jump_height_counter += game_step * JumpingSpeedCoef;
		player.y_accel = -player.step;
		//Jump
	}
	else {
		player.in_jump = false;
		player.current_jump_frame = 0.f;
		player.jump_height_counter = 0;
	}
	
	// Box & Sprite steps

	PlayerAnimations(player, deltaTime);

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

	float health_in_percent = player.health_points / player.max_health_points;
	player.hp_bar->bar_sprite.setTextureRect(IntRect(0, 0, PlayerHpBarWidth, PlayerHpBarHeight));
	Vector2f view_center = player.view->getCenter();
	Vector2f view_size = player.view->getSize();
	player.hp_bar->bar_sprite.setPosition(view_center.x - (view_size.x / 2.f), view_center.y - (view_size.y / 2.f));
	player.hp_bar->strip_sprite.setTextureRect(IntRect(0, PlayerHpBarHeight, PlayerHpStripWidth * health_in_percent, PlayerHpStripHeight));
	player.hp_bar->strip_sprite.setPosition(player.hp_bar->bar_sprite.getGlobalBounds().left + 56, player.hp_bar->bar_sprite.getGlobalBounds().top + 7);
}

void CheckPlayerCollisions(Player& player, Game& game) {
	bool delete_enemy = false;
	player.on_ground = false;
	for (int i = 0; i < game.obj[0].size(); i++) {
		FloatRect& map_bounds = game.obj[0][i].rect;
		FloatRect& player_box = game.obj[0][player.obj_number].rect;
		FloatRect player_sprite = player.sprite.getGlobalBounds();
		if (player_box.intersects(map_bounds)) {
			if (game.obj[0][i].name == "trap") {
				player.in_jump = true;
				player.health_points -= 10.f;
			}
			if (game.obj[0][i].name == "solid") {

				bool upper_collision = false;
				bool bottom_collision = false;
				bool player_higher_than_object = player_box.top + player_box.height - 5 < map_bounds.top;
				bool player_less_than_object = player_box.top + 5 > map_bounds.top + map_bounds.height;

				if (player.y_accel > 0 && player_higher_than_object) {// Check upper collision 
					player.jump_animation = false;
					player.on_ground = true;
					player_box.top = map_bounds.top - player_box.height + 1;
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
						if (enemy->health_points <= 0) {
							delete_enemy = true;
							delete *iter;
							game.enemy_list->remove(*iter);
							game.obj[0].erase(game.obj[0].begin() + i);
							i--;
							break;
						}
						else {
							if (!player.attack_occured) {
								enemy->health_points -= player.damage;
								player.attack_occured = true;
							}
							
						}
						cout << enemy->health_points << endl;
					}
				}
				if (delete_enemy) {
					for (std::list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
						Enemy* enemy = *iter;
						if (int(enemy->obj_number) > i) {
							enemy->obj_number--;
						}

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
	level->LoadFromFile("map2.tmx");
}

void EnemyAdd(Game& game) { // Будет несколько вариков мобов
	Enemy* enemy = new Enemy();
	enemy->hp_bar = new HpBar();
	enemy->hp_bar->bar_texture.loadFromFile("bars.png");
	enemy->hp_bar->bar_sprite.setTexture(enemy->hp_bar->bar_texture);
	enemy->hp_bar->strip_sprite.setTexture(enemy->hp_bar->bar_texture);
	stringstream number;
	number << game.enemy_list->size();
	enemy->name = "enemy" + number.str();
	char obj_number = 1;
	while (game.obj[0][obj_number].name != enemy->name) {
		obj_number++;
	}
	enemy->health_points = 50.f;
	enemy->max_health_points = enemy->health_points = 30.f;
	enemy->field_of_view = 300.f;
	enemy->obj_number = obj_number;
	enemy->state = NONE;
	enemy->x_accel = 0;
	enemy->y_accel = 0;
	enemy->image.loadFromFile("BIGknight_enemy.png");
	enemy->texture.loadFromImage(enemy->image);
	enemy->sprite.setTexture(enemy->texture);
	enemy->sprite.setTextureRect(sf::IntRect(78, 0, XEnemySize, YEnemySize));
	enemy->max_jump = 75.f;
	enemy->damage = 10;
	game.enemy_list->push_back(enemy);

}

void PlayerInit(Game& game) {
	Player *& player = game.player;
	player = new Player();
	char obj_number = 1;
	while (game.obj[0][obj_number].name != "player") {
		obj_number++;
	}
	player->health_points = game.player->max_health_points = 150.f;;
	player->damage = WhiteWeaponDamage;
	player->obj_number = obj_number;
	player->x_accel = 0;
	player->y_accel = 0;
	player->hp_bar = new HpBar();
	player->hp_bar->bar_texture.loadFromFile("new_bars.png");
	player->hp_bar->bar_sprite.setTexture(player->hp_bar->bar_texture);
	player->hp_bar->strip_sprite.setTexture(player->hp_bar->bar_texture);
	player->image.loadFromFile("hero.png");
	player->texture.loadFromImage(game.player->image);
	player->sprite.setTexture(game.player->texture);
	player->sprite.setTextureRect(IntRect(0, 0, 22, 42));
	player->max_jump = 75.f;
}

void EnemyListInit(list<Enemy*>*& enemy_list) {
	enemy_list = new list<Enemy*>();
}

void ObjectsInit(vector<Object>*& obj, Level* level) {
	obj = new vector<Object>();
	*obj = level->GetAllObjects();
}

void ViewInit(Game & game) {
	game.player->view = new sf::View();
	game.player->view->reset(sf::FloatRect(0, 0, game.window->getSize().x, game.window->getSize().y));
	if (game.lvl->tileHeight * game.lvl->height < game.window->getSize().y) {
		game.player->view->zoom(float(game.lvl->tileHeight * game.lvl->height) / game.window->getSize().y);
	}
}


void GameInit(Game& game) {
	game.window = new RenderWindow(VideoMode(WindowWidth, WindowHeight), "From the Shadow of Underdark");
	LevelInit(game.lvl);
	ObjectsInit(game.obj, game.lvl);
	PlayerInit(game);
	ViewInit(game);
	EnemyListInit(game.enemy_list);
	int enemies = game.lvl->GetAllObjects().size() - game.lvl->GetObjects("solid").size() - game.lvl->GetObjects("trap").size() - 1;
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
			if (player_box.top + player_box.height < enemy_box.top) {
				enemy->jump = true;
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.on_ground) {
			player.in_jump = true;
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !player.in_jump) {
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
	window.draw(game.player->hp_bar->bar_sprite);
	window.draw(game.player->hp_bar->strip_sprite);
	for (list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
		Enemy* enemy = *iter;
		window.draw(enemy->sprite);
		window.draw(enemy->hp_bar->bar_sprite);
		window.draw(enemy->hp_bar->strip_sprite);
	}
	window.display();
}
