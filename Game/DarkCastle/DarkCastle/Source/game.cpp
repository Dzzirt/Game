#include <sstream>
#include "../Headers/game.h"
#include <complex>


using namespace sf;
using namespace std;

void LevelInit(Level& level) {
	level.LoadFromFile("Resourses/map.tmx");
}

void EnemyListInit(list<Enemy*>*& enemy_list) {
	enemy_list = new list<Enemy*>();
}

void GameInit(Game& game) {
	game.window = new RenderWindow(VideoMode(WindowWidth, WindowHeight), "Dark Castle");
	game.lvl = new Level();
	game.player = new Player();
	LevelInit(*game.lvl);
	EnemyListInit(game.enemy_list);
	
	FloatRect player_rect = GetPlayerRectFromLvl(*game.lvl);
	PlayerInit(*game.player, player_rect);

	int spearmans_count = GetEnemiesCount(*game.lvl, SPEARMAN);

	for (int i = 0; i < spearmans_count; i++) {
		Enemy* enemy = new Enemy();
		FloatRect enemy_rect = GetEnemyRectFromLvl(*game.lvl, SPEARMAN, i);
		EnemyInit(*enemy, SPEARMAN, enemy_rect);
		game.enemy_list->push_back(enemy);
	}
}

void ProcessEnemiesEvents(Enemy& enemy, Type type) { }

void ProcessEvents(RenderWindow& window, Game& game) {
	for (list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
		Enemy* enemy = *iter;
		ProcessEnemiesEvents(*enemy, SPEARMAN);
	}
	ProcessPlayerEvents(window, *game.player);
}

void Update(Game& game, const Time& deltaTime) {
	PlayerUpdate(*game.player, *game.lvl, deltaTime);
	ViewUpdate(*game.player->view, *game.window, *game.player->logic->movement, *game.lvl, game.player->visual->animation->frame->displacement);
	PlayerHpBarUpdate(*game.player->logic->fight, *game.player->view);
	for (list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
		Enemy* enemy = *iter;
		EnemyUpdate(*enemy, deltaTime, *game.lvl);
	}
	CheckPlayerAndEnemyCollision(game);
}

void Render(RenderWindow& window, Game& game) {
	HpBar& player_hp = *game.player->logic->fight->hp_bar;
	Sprite& player_sprite = game.player->visual->animation->frame->sprite;
	game.lvl->Draw(window);
	window.setView(*game.player->view);
	window.draw(player_sprite);
	window.draw(player_hp.bar_sprite);
	window.draw(player_hp.strip_sprite);
	for (list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
		Enemy* enemy = *iter;
		HpBar enemy_hp = *enemy->logic->fight->hp_bar;
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
			if (player.logic->fight->is_dead) {
				cout << "Player is dead!";
				break;
			}
			if (enemy->logic->fight->is_dead) {
				game.enemy_list->remove(*iter);
				break;
			}
		}
	}
}

void PlayerEnemyCollision(const Player& player, Enemy& enemy) {
	Animation& player_anim = *player.visual->animation;
	FightLogic& enemy_fight = *enemy.logic->fight;
	FloatRect player_sprite = player.visual->animation->frame->sprite.getGlobalBounds();
	FloatRect& enemy_rect = *enemy.visual->rect;
	float& player_damage = player.logic->fight->damage;
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
	FightLogic& player_fight = *player.logic->fight;
	FloatRect enemy_sprite = enemy.visual->animation->frame->sprite.getGlobalBounds();
	FloatRect& player_rect = *player.visual->rect;
	const float& enemy_damage = enemy.logic->fight->damage;
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