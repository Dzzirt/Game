#include "game.h"
#include <sstream>

using namespace std;



void LevelInit(Level *& level) {
	level = new Level();
	level->LoadFromFile("map.tmx");
}

void EnemyAdd(Game & game) {
	Enemy * enemy = new Enemy();
	stringstream number;
	number << game.enemy_list->size();
	sf::Rect<float> enemy_rect = game.lvl->GetObject("enemy" + number.str()).rect;
	enemy->state = NONE;
	enemy->x_pos = enemy_rect.left;
	enemy->y_pos = enemy_rect.top;
	enemy->x_accel = 0;
	enemy->y_accel = 0;
	enemy->image.loadFromFile("enemy.png");
	enemy->texture.loadFromImage(enemy->image);
	enemy->sprite.setTexture(enemy->texture);
	enemy->sprite.setTextureRect(sf::IntRect(0, 0, XEnemySize, YEnemySize));
	enemy->sprite.setPosition(enemy->x_pos, enemy->y_pos);
	enemy->max_jump = enemy->sprite.getGlobalBounds().height / 2;
	enemy->obj = game.lvl->GetAllObjects();
	game.enemy_list->push_back(enemy);
	
}

void EnemyListInit(std::list<Enemy*> *& enemy_list) {
	enemy_list = new list<Enemy*>();
}

void GameInit(Game& game) {
	LevelInit(game.lvl);
	PlayerInit(game.player, *game.lvl);
	ViewInit(game.player->view);
	EnemyListInit(game.enemy_list);
	for (int i = 0; i < 2; i++) {
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
	PlayerUpdate(*game.player, deltaTime);
	for (list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
		Enemy * enemy = *iter;
		EnemyUpdate(*enemy, deltaTime);
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
