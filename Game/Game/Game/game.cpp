#include "game.h"
#include <sstream>
#include "map.h"
using namespace sf;
using namespace std;

void EnemyUpdate(Enemy & enemy, const sf::Time& deltaTime, Game & game) {
	switch (enemy.state) {
	case LEFT:
		enemy.x_accel = -enemy.step;
		break;
	case RIGHT:
		enemy.x_accel = enemy.step;
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
		enemy.y_accel = enemy.step;
	}
	float delta_x = enemy.x_accel * deltaTime.asSeconds();
	float delta_y = enemy.y_accel * deltaTime.asSeconds();

	game.obj[0][enemy.obj_number].rect.left += delta_x;
	game.obj[0][enemy.obj_number].rect.top += delta_y;

	

	CheckEnemyCollisions(enemy, game);
	//cout << enemy.box.left << "   " << enemy.box.top << '\n';
	enemy.x_pos = game.obj[0][enemy.obj_number].rect.left;
	enemy.y_pos = game.obj[0][enemy.obj_number].rect.top;
	enemy.sprite.setPosition(enemy.x_pos, enemy.y_pos);
}

void CheckEnemyCollisions(Enemy & enemy, Game & game) {
	for (size_t i = 0; i < game.obj[0].size(); i++) {
		sf::FloatRect & map_bounds = game.obj[0][i].rect;
		sf::FloatRect & enemy_box = game.obj[0][enemy.obj_number].rect;
		sf::FloatRect  enemy_sprite = enemy.sprite.getGlobalBounds();
		//std::cout << game.lvl.GetObject("enemy").rect.left;
		//проходимся по объектамs

		if (enemy_box.intersects(map_bounds))//проверяем пересечение игрока с объектом
		{

			if (game.obj[0][i].name == "solid") {
				bool upper_collision = false;
				bool bottom_collision = false;
				bool enemy_higher_than_object = enemy_box.top + enemy_box.height - 4 < map_bounds.top;
				bool enemy_less_than_object = enemy_box.top + 4 > map_bounds.top + map_bounds.height;

				if (enemy.y_accel > 0 && enemy_higher_than_object) { // Check upper collision 
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
				}
				else if (enemy.x_accel > 0 && !upper_collision && !bottom_collision) { // Check collision with right side
					enemy_box.left -= enemy_box.left + enemy_box.width - map_bounds.left;
				}
			}
		}
		if (enemy_sprite.intersects(map_bounds)) {
			cout << game.obj[0][i].name;
			if (game.obj[0][i].name == "player") {
				cout << "kek";
				// Доделать
			}
		}
	}
	enemy.x_accel = 0;
	enemy.y_accel = 0;
}

void PlayerUpdate(Player& player, const sf::Time& deltaTime, Game & game) {
	switch (player.state) {
	case LEFT:
		player.x_accel = -player.step;
		player.sprite.setTextureRect(IntRect(126, 0, -48, 84));
		player.displacement = 0;
		player.is_attack = false;
		break;
	case RIGHT:
		player.x_accel = player.step;
		player.sprite.setTextureRect(IntRect(78, 0, 48, 84));
		player.displacement = 0;
		player.is_attack = false;
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
	float delta_x = player.x_accel * deltaTime.asSeconds();
	float delta_y = player.y_accel * deltaTime.asSeconds();

	game.obj[0][player.obj_number].rect.left += delta_x;
	game.obj[0][player.obj_number].rect.top += delta_y;
	//cout << "                                    " << player.x_pos + player.sprite.getGlobalBounds().width << "   " << player.y_pos + player.sprite.getGlobalBounds().height << '\n';
	CheckPlayerCollisions(player, game);
	
	player.x_pos = game.obj[0][player.obj_number].rect.left - player.displacement;
	player.y_pos = game.obj[0][player.obj_number].rect.top;
	player.sprite.setPosition(player.x_pos, player.y_pos);
	




	GetPlayerCoordinateForView(*player.view, player.x_pos + 24, player.y_pos + 42);
}

void CheckPlayerCollisions(Player& player, Game & game) {
	for (size_t i = 0; i < game.obj[0].size(); i++) {
		FloatRect& map_bounds = game.obj[0][i].rect;
		FloatRect& player_box = game.obj[0][player.obj_number].rect;
		FloatRect  player_sprite = player.sprite.getGlobalBounds();
		if (player_box.intersects(map_bounds)) {
			if (game.obj[0][i].name == "solid") {
				bool upper_collision = false;
				bool bottom_collision = false;
				bool player_higher_than_object = player_box.top + player_box.height - 10 < map_bounds.top;
				bool player_less_than_object = player_box.top + 10 > map_bounds.top + map_bounds.height;

				if (player.y_accel > 0 && player_higher_than_object) { // Check upper collision 
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
		if (player_sprite.intersects(map_bounds) && player.is_attack) {
			if (game.obj[0][i].name.substr(0, 5) == "enemy") {
				for (std::list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
					Enemy * enemy = *iter;
					if (enemy->name == game.obj[0][i].name) {
						delete *iter;
						game.enemy_list->remove(*iter);
						game.obj[0].erase(game.obj[0].begin() + i);
						break;
					}
				}
			}
		}
	}
	player.x_accel = 0;
	player.y_accel = 0;
}

void LevelInit(Level *& level) {
	level = new Level();
	level->LoadFromFile("map.tmx");
}

void EnemyAdd(Game & game) {
	Enemy * enemy = new Enemy();
	stringstream number;
	number << game.enemy_list->size();
	enemy->name = "enemy" + number.str();
	char obj_number = 1;
	while (game.obj[0][obj_number].name != enemy->name) {
		obj_number++;
	}
	enemy->obj_number = obj_number;
	enemy->box.width = 30;
	enemy->box.height = 60;
	enemy->state = NONE;
	enemy->x_accel = 0;
	enemy->y_accel = 0;
	enemy->image.loadFromFile("enemy.png");
	enemy->texture.loadFromImage(enemy->image);
	enemy->sprite.setTexture(enemy->texture);
	enemy->sprite.setTextureRect(sf::IntRect(0, 0, XEnemySize, YEnemySize));
	enemy->sprite.setPosition(enemy->x_pos, enemy->y_pos);
	enemy->max_jump = enemy->sprite.getGlobalBounds().height / 2;
	game.enemy_list->push_back(enemy);
	
}

void PlayerInit(Game & game) {
	game.player = new Player();
	char obj_number = 1;
	while (game.obj[0][obj_number].name != "player") {
		obj_number++;
	}
	game.player->obj_number = obj_number;
	game.player->box.width = 48;
	game.player->box.height = 84;
	game.player->x_accel = 0;
	game.player->y_accel = 0;
	game.player->image.loadFromFile("hero_spritesheet.png");
	game.player->texture.loadFromImage(game.player->image);
	game.player->sprite.setTexture(game.player->texture);
	game.player->sprite.setTextureRect(IntRect(78, 0, 48, 84));
	game.player->sprite.setPosition(game.player->x_pos, game.player->y_pos);
	game.player->max_jump = game.player->sprite.getGlobalBounds().height / 2;
}
void EnemyListInit(list<Enemy*> *& enemy_list) {
	enemy_list = new list<Enemy*>();
}

void ObjectsInit(vector<Object> *& obj, Level * level) {
	obj = new vector<Object>();
	*obj = level->GetAllObjects();
}


void GameInit(Game& game) {
	LevelInit(game.lvl);
	ObjectsInit(game.obj, game.lvl);
	PlayerInit(game);
	ViewInit(game.player->view);
	EnemyListInit(game.enemy_list);
	for (int i = 0; i < 1; i++) {
		EnemyAdd(game);
	}
}

void ProcessEvents(sf::RenderWindow& window, Game& game) {
	Player& player = *game.player;
	sf::View& view = *game.player->view;
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			float mouse_global_x = sf::Mouse::getPosition(window).x + game.player->view->getCenter().x - (window.getSize().x / 2);
			if (mouse_global_x > game.player->box.left + 24) {
				player.sprite.setTextureRect(sf::IntRect(0, 0, 78, 84));
				player.is_attack = true;
				player.state = NONE;
			}
			if (mouse_global_x < game.player->box.left + 24) {
				player.sprite.setTextureRect(sf::IntRect(78, 0, -78, 84));
				player.displacement = 30;
				player.is_attack = true;
				player.state = NONE;
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
		Enemy * enemy = *iter;
		EnemyUpdate(*enemy, deltaTime, game);
	}
}

void Render(sf::RenderWindow& window, Game& game) {
	game.lvl->Draw(window);
	window.setView(*game.player->view);
	window.draw(game.player->sprite);
	for (list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
		Enemy * enemy = *iter;
		window.draw(enemy->sprite);
	}
	window.display();
}
