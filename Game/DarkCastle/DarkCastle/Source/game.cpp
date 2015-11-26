#include <sstream>
#include "../Headers/game.h"


using namespace sf;
using namespace std;


Game* CreateGame() {
	Game* game = new Game();
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
	// � ��. ���� ��������
	return list;
}

std::list<Bonus*>* CreateBonusList(Level& level) {
	std::list<Bonus*>* list = new std::list<Bonus*>();
	BonusListInit(*list, level, HP_REGEN);
	BonusListInit(*list, level, ATK_UP);
	BonusListInit(*list, level, SPEED_UP);
	// � ��. ���� ��������
	return list;
}

void EnemyListInit(list<Enemy*>& enemy_list, Level& level, Type type) {
	int enemies_count = GetEnemiesCount(level, type);
	for (int i = 0; i < enemies_count; i++) {
		Enemy* enemy = CreateEnemy(level, i);
		enemy_list.push_back(enemy);
	}
}


void BonusListInit(list<Bonus*>& bonus_list, Level& level, BonusType type) {
	int bonuses_count = GetBonusesCount(level, type);
	for (int i = 0; i < bonuses_count; i++) {
		Bonus* bonus = CreateBonus(level, type, i);
		bonus_list.push_back(bonus);
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
	game.bonus_list = CreateBonusList(*game.lvl);
}

void DestroyGame(Game*& game) {
	DestroyWindow(game->window);
	DestroyLevel(game->lvl);
	DestroyPlayer(game->player);
	DestroyEnemyList(game->enemy_list);
	delete game;
}


void ProcessEvents(Game& game) {
	RenderWindow& window = *game.window;
	for (list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
		Enemy* enemy = *iter;
		ProcessEnemiesEvents(*enemy, *game.player->visual->rect);
	}
	ProcessPlayerEvents(window, *game.player, *game.lvl);
}

void Update(Game& game, const Time& deltaTime) {
	PlayerUpdate(*game.player, *game.lvl, deltaTime);
	ViewUpdate(*game.player->view, *game.window, *game.player->movement, *game.lvl, game.player->visual->animation->frame->displacement);
	HpBarUpdate(*game.player->fight->hp_bar, *game.player->view, game.player->fight->health_points);
	for (list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
		Enemy* enemy = *iter;
		EnemyUpdate(*enemy, deltaTime, *game.lvl);
	}
	CheckDynamicObjCollisions(game);
}

void Render(Game& game) {

	VisualHpBar& player_hp = *game.player->fight->hp_bar->visual_hp;
	Sprite& player_sprite = game.player->visual->animation->frame->sprite;
	RenderWindow& window = *game.window;

	game.lvl->Draw(window);
	window.setView(*game.player->view);
	for (list<Bonus*>::iterator iter = game.bonus_list->begin(); iter != game.bonus_list->end(); ++iter) {
		Bonus* bonus = *iter;
		window.draw(bonus->bonus_visual->sprite);
	}
	window.draw(player_sprite);
	window.draw(player_hp.bar_sprite);
	window.draw(player_hp.strip_sprite);
	for (list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
		Enemy* enemy = *iter;
		VisualHpBar enemy_hp = *enemy->fight->hp_bar->visual_hp;
		Sprite enemy_sprite = enemy->visual->animation->frame->sprite;
		window.draw(enemy_sprite);
		window.draw(enemy_hp.bar_sprite);
		window.draw(enemy_hp.strip_sprite);
	}

	window.display();
}

void ProcessEnemiesEvents(Enemy& enemy, FloatRect& player_box) {
	Animation& anim = *enemy.visual->animation;
	FloatRect& enemy_box = *enemy.visual->rect;
	float enemy_box_right = enemy_box.left + enemy_box.width;
	float player_box_right = player_box.left + player_box.width;
	bool right_detect = player_box.left - enemy.ai->field_of_view <= enemy_box_right && player_box.left >= enemy_box.left;
	bool left_detect = player_box_right + enemy.ai->field_of_view >= enemy_box.left && player_box.left <= enemy_box.left;
	bool not_too_higher = player_box.top + player_box.height >= enemy_box.top - player_box.height;
	if (enemy.ai->state == NOT_DETECT) {
		if (left_detect || right_detect && not_too_higher) {
			enemy.ai->state = DETECT;
		}
	}
	else if (enemy.ai->state == DETECT) {
		if (left_detect) {
			enemy.movement->state = LEFT;
		}
		else if (right_detect) {
			enemy.movement->state = RIGHT;
		}
		else enemy.movement->state = NONE;
		bool close_from_left = enemy_box_right > player_box.left && enemy_box_right < player_box_right;
		bool close_from_right = enemy_box.left < player_box_right && enemy_box.left > player_box.left;
		if (close_from_left) {
			anim.right_attack = true;
			anim.left_attack = false;
			enemy.movement->state = NONE;
		}
		else if (close_from_right) {
			anim.left_attack = true;
			anim.right_attack = false;
			enemy.movement->state = NONE;
		}
	}
}

void CheckDynamicObjCollisions(Game& game) {
	Player& player = *game.player;
	vector<Object> map_objects = game.lvl->GetAllObjects();
	list<Enemy*>::iterator list_begin = game.enemy_list->begin();
	list<Enemy*>::iterator list_end = game.enemy_list->end();
	for (list<Bonus*>::iterator iter = game.bonus_list->begin(); iter != game.bonus_list->end(); ++iter) {
		Bonus* bonus = *iter;
		PlayerBonusCollision(player, *bonus);
		if (bonus->picked_up) {
			DestroyBonus(*bonus);
			game.bonus_list->remove(*iter);
			break;
		}
	}
	for (list<Enemy*>::iterator iter = list_begin; iter != list_end; ++iter) {
		Enemy* enemy = *iter;
		PlayerEnemyCollision(player, *enemy);
		EnemyPlayerCollision(*enemy, player);
		if (player.fight->is_dead) {
			cout << "Player is dead!";
			break;
		}
		if (enemy->fight->is_dead) {
			DestroyEnemy(enemy);
			game.enemy_list->remove(*iter);
			break;

		}
	}
}

void PlayerEnemyCollision(const Player& player, Enemy& enemy) {
	Animation& player_anim = *player.visual->animation;
	FightLogic& enemy_fight = *enemy.fight;
	float & enemy_hp = enemy.fight->health_points;
	FloatRect player_sprite = player.visual->animation->frame->sprite.getGlobalBounds();
	FloatRect& enemy_rect = *enemy.visual->rect;
	float& player_damage = player.fight->damage;
	bool is_hit = int(player_anim.current_attack_frame) == 3;
	cout << is_hit << endl;
	if (player_sprite.intersects(enemy_rect) && is_hit) {
		if (enemy_hp <= 0) {
			enemy_fight.is_dead = true;
		}
		else {
			enemy_hp -= player_damage;
		}
		player_damage = 0;
	}
	else {
		player_damage = CPlayerDamage;
	}
}

void PlayerBonusCollision(const Player& player, Bonus& bonus) {
	FloatRect player_sprite = player.visual->animation->frame->sprite.getGlobalBounds();
	FloatRect bonus_sprite = bonus.bonus_visual->sprite.getGlobalBounds();
	FightLogic& fight = *player.fight;
	Movement& movement = *player.movement;
	if (player_sprite.intersects(bonus_sprite)) {
		bonus.picked_up = true;
		switch (bonus.bonus_type) {
			case HP_REGEN:
				fight.health_points += bonus.value;
				break;
			case SPEED_UP:
				movement.step *= bonus.value;
				break;
			case ATK_UP:
				fight.damage *= bonus.value;
				break;
		}
	}

}

void EnemyPlayerCollision(const Enemy& enemy, Player& player) {
	Animation& enemy_anim = *enemy.visual->animation;
	FightLogic& player_fight = *player.fight;
	float & player_hp = player.fight->health_points;
	FloatRect enemy_sprite = enemy.visual->animation->frame->sprite.getGlobalBounds();
	FloatRect& player_rect = *player.visual->rect;
	float& enemy_damage = enemy.fight->damage;
	bool is_hit = int(enemy_anim.current_attack_frame) == 4;

	if (enemy_sprite.intersects(player_rect) && is_hit) {
		if (player_hp <= 0) {
			player_fight.is_dead = true;
		}
		else {
			player_hp -= enemy_damage;
		}
		enemy_damage = 0;
	}
	else {
		enemy_damage = CEnemyDamage;
	}
}
