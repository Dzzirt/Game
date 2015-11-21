#include <sstream>
#include "../Headers/game.h"


using namespace sf;
using namespace std;


Game* CreateGame() {
	Game * game = new Game();
	GameInit(*game);
	return game;
}
Level* CreateLevel() {
	Level* level = new Level();
	LevelInit(*level);
	return level;
}

void LevelInit(Level& level) {
	level.LoadFromFile("Resourses/map.tmx");
}

void DestroyLevel(Level*& level) {
	delete level;
}

void DestroyWindow(RenderWindow*& window) {
	delete window;
}

RenderWindow* CreateRenderWindow() {
	return new RenderWindow(VideoMode(WindowWidth, WindowHeight), "Dark Castle");
}

std::list<Enemy*>* CreateEnemyList(Level& level) {
	std::list<Enemy*>* list = new std::list<Enemy*>();
	EnemyListInit(*list, level, SPEARMAN);
	// и др. типы монстров
	return list;
}

void EnemyListInit(list<Enemy*>& enemy_list, Level& level, Type type) {
	int enemies_count = GetEnemiesCount(level, type);
	for (int i = 0; i < enemies_count; i++) {
		Enemy* enemy = CreateEnemy(level, i);
		enemy_list.push_back(enemy);
	}
}

void DestroyEnemyList(list<Enemy*>*& enemy_list) {
	list<Enemy*>::iterator begin = enemy_list->begin();
	list<Enemy*>::iterator end = enemy_list->end();
	for (list<Enemy*>::iterator iter = begin; iter != end; ++iter) {
		DestroyEnemy(*iter);
	}
	delete enemy_list;
}

void GameInit(Game& game) {
	game.window = CreateRenderWindow();
	game.lvl = CreateLevel();
	game.player = CreatePlayer(*game.lvl);
	game.enemy_list = CreateEnemyList(*game.lvl);
}

void DestroyGame(Game*& game) {
	DestroyWindow(game->window);
	DestroyLevel(game->lvl);
	DestroyPlayer(game->player);
	DestroyEnemyList(game->enemy_list);
	delete game;
}

void ProcessEnemiesEvents(Enemy& enemy, Type type) { }

void ProcessEvents(Game& game) {
	RenderWindow& window = *game.window;
	for (list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
		Enemy* enemy = *iter;
		ProcessEnemiesEvents(*enemy, SPEARMAN);
	}
	ProcessPlayerEvents(window, *game.player, *game.lvl);
}

void Update(Game& game, const Time& deltaTime) {
	PlayerUpdate(*game.player, *game.lvl, deltaTime);
	ViewUpdate(*game.player->view, *game.window, *game.player->movement, *game.lvl, game.player->visual->animation->frame->displacement);
	PlayerHpBarUpdate(*game.player->fight, *game.player->view);
	for (list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
		Enemy* enemy = *iter;
		EnemyUpdate(*enemy, deltaTime, *game.lvl);
	}
	CheckPlayerAndEnemyCollision(game);
}

void Render(Game& game) {
	HpBar& player_hp = *game.player->fight->hp_bar;
	Sprite& player_sprite = game.player->visual->animation->frame->sprite;
	RenderWindow& window = *game.window;
	game.lvl->Draw(window);
	window.setView(*game.player->view);
	window.draw(player_sprite);
	window.draw(player_hp.bar_sprite);
	window.draw(player_hp.strip_sprite);
	for (list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
		Enemy* enemy = *iter;
		HpBar enemy_hp = *enemy->fight->hp_bar;
		Sprite enemy_sprite = enemy->visual->animation->frame->sprite;
		window.draw(enemy_sprite);
		window.draw(enemy_hp.bar_sprite);
		window.draw(enemy_hp.strip_sprite);
	}
	window.display();
}

void CheckPlayerAndEnemyCollision(Game& game) {
	Player& player = *game.player;
	vector<Object> map_objects = game.lvl->GetAllObjects();
	list<Enemy*>::iterator list_begin = game.enemy_list->begin();
	list<Enemy*>::iterator list_end = game.enemy_list->end();
	for (int i = 0; i < map_objects.size(); i++) {
		list_begin = game.enemy_list->begin();
		list_end = game.enemy_list->end();
		for (list<Enemy*>::iterator iter = list_begin; iter != list_end; ++iter) {
			Enemy* enemy = *iter;
			PlayerEnemyCollision(player, *enemy);
			EnemyPlayerCollision(*enemy, player);
			if (player.fight->is_dead) {
				cout << "Player is dead!";
				break;
			}
			if (enemy->fight->is_dead) {
				game.enemy_list->remove(*iter);
				break;
			}
		}
	}
}

void PlayerEnemyCollision(const Player& player, Enemy& enemy) {
	Animation& player_anim = *player.visual->animation;
	FightLogic& enemy_fight = *enemy.fight;
	FloatRect player_sprite = player.visual->animation->frame->sprite.getGlobalBounds();
	FloatRect& enemy_rect = *enemy.visual->rect;
	float& player_damage = player.fight->damage;
	bool is_hit = int(player_anim.current_attack_frame) == 3;
	if (player_sprite.intersects(enemy_rect) && is_hit) {
		if (enemy_fight.health_points <= 0) {
			enemy_fight.is_dead = true;
		}
		else {
			enemy_fight.health_points -= player_damage;
		}
		player_damage = 0;
	}
	else {
		player_damage = CPlayerDamage;
	}
}

void EnemyPlayerCollision(const Enemy& enemy, Player& player) {
	Animation& enemy_anim = *enemy.visual->animation;
	FightLogic& player_fight = *player.fight;
	FloatRect enemy_sprite = enemy.visual->animation->frame->sprite.getGlobalBounds();
	FloatRect& player_rect = *player.visual->rect;
	const float& enemy_damage = enemy.fight->damage;
	bool is_hit = enemy_anim.current_attack_frame == 4;

	if (enemy_sprite.intersects(player_rect) && is_hit) {
		if (player_fight.health_points <= 0) {
			player_fight.is_dead = true;
		}
		else {
			player_fight.health_points -= enemy_damage;
		}
	}
}
