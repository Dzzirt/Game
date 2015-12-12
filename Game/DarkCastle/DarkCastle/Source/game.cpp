#include <sstream>
#include "../Headers/game.h"
#include <chrono>

using namespace sf;
using namespace std;


Game* CreateGame() {
	Game* game = new Game();
	GameInit(*game);
	return game;
}

RenderWindow* CreateRenderWindow() {
	return new RenderWindow(VideoMode(WindowWidth, WindowHeight), "Dark Castle");
}

std::list<Enemy*>* CreateEnemyList(Resourses& res) {
	std::list<Enemy*>* list = new std::list<Enemy*>();
	EnemyListInit(*list, res, SPEARMAN);
	return list;
}

std::list<Bonus*>* CreateBonusList(Resourses& res) {
	auto list = new std::list<Bonus*>();
	BonusListInit(*list, res, HP_REGEN);
	BonusListInit(*list, res, ATK_UP);
	BonusListInit(*list, res, SPEED_UP);
	return list;
}

std::list<DurationController*>* CreateDurationControllerVec() {
	std::list<DurationController*>* controllers = new std::list<DurationController*>();
	return controllers;
}

void EnemyListInit(list<Enemy*>& enemy_list, Resourses& res, Type type) {
	int enemies_count = GetEnemiesCount(*res.lvl, type);
	for (int i = 0; i < enemies_count; i++) {
		Enemy* enemy = CreateEnemy(res, i);
		enemy_list.push_back(enemy);
	}
}


void BonusListInit(list<Bonus*>& bonus_list, Resourses& res, BonusType type) {
	int bonuses_count = GetBonusesCount(*res.lvl, type);
	for (int i = 0; i < bonuses_count; i++) {
		Bonus* bonus = CreateBonus(res, type, i);
		bonus_list.push_back(bonus);
	}
}



void GameInit(Game& game) {
	game.window = CreateRenderWindow();
	game.view = CreateView();
	game.res = CreateResourses();
	game.player = CreatePlayer(*game.res);
	game.enemy_list = CreateEnemyList(*game.res);
	game.bonus_list = CreateBonusList(*game.res);
	game.b_panel = CreateBonusesPanel();
	game.dur_ctrl_list = CreateDurationControllerVec();
	game.game_sounds = CreateGameSounds();
}


void RestartGame(Game *& game) {
	DestroyGame(game);
	game = CreateGame();
}

void ProcessEvents(Game*& game) {
	RenderWindow& window = *game->window;
	Event event;
	for (list<Enemy*>::iterator iter = game->enemy_list->begin(); iter != game->enemy_list->end(); ++iter) {
		Enemy* enemy = *iter;
		ProcessEnemiesEvents(*enemy, *game->player->visual->rect);
	}

	while (window.pollEvent(event)) {
		ProcessPlayerEvents(window, event, *game->player, *game->game_sounds, *game->res->lvl, *game->view);
		if (Keyboard::isKeyPressed(Keyboard::R) && game->player->fight->is_dead) {
			RestartGame(game);
		}
	}
}

void Update(Game& game, const Time& deltaTime) {
	PlayerUpdate(*game.player, *game.res->lvl, deltaTime);
	ViewUpdate(*game.view, *game.player->movement, *game.res->lvl, game.player->visual->animation->frame->displacement);
	HpBarUpdate(*game.player->hp_bar, *game.view, game.player->fight->health_points);
	BonusesPanelUpdate(*game.b_panel, *game.view);
	for (Enemy * enemy : *game.enemy_list) {
		EnemyUpdate(*enemy, deltaTime, *game.res->lvl);
	}
	for (DurationController *& ctrl : *game.dur_ctrl_list) {
		DuratonControllerUpdate(*ctrl, deltaTime);
	}
	for (DurationController *& ctrl : *game.dur_ctrl_list) {
		if (CheckBonusEffectEnd(*game.player, *ctrl, *game.res->config)) {
			DestroyDurationController(*ctrl);
			game.dur_ctrl_list->remove(ctrl);
			break;
		}
	}
	CheckDynamicObjCollisions(game);
}


void Render(Game& game) {
	RenderWindow& window = *game.window;
	if (game.player->fight->is_dead) {
		game.view->setCenter(WindowWidth / 2.f, WindowHeight / 2.f);
		window.setView(*game.view);
		Sprite die_screen;
		Texture texture;
		texture.loadFromFile("Resourses/die_msg.png");
		die_screen.setTexture(texture);
		window.draw(die_screen);
	}
	else {
		VisualHpBar& player_hp = *game.player->hp_bar->visual_hp;
		Sprite& player_sprite = game.player->visual->animation->frame->sprite;
		game.res->lvl->Draw(window);
		window.setView(*game.view);
		for (list<Bonus*>::iterator iter = game.bonus_list->begin(); iter != game.bonus_list->end(); ++iter) {
			Bonus* bonus = *iter;
			window.draw(bonus->bonus_visual->sprite);
		}
		window.draw(player_sprite);
		window.draw(player_hp.bar_sprite);
		window.draw(player_hp.strip_sprite);
		for (list<Enemy*>::iterator iter = game.enemy_list->begin(); iter != game.enemy_list->end(); ++iter) {
			Enemy* enemy = *iter;
			VisualHpBar& enemy_hp = *enemy->hp_bar->visual_hp;
			Sprite& enemy_sprite = enemy->visual->animation->frame->sprite;
			window.draw(enemy_sprite);
			window.draw(enemy_hp.bar_sprite);
			window.draw(enemy_hp.strip_sprite);
		}
		DrawBonusesPanel(*game.b_panel, *game.window);
	}
	window.display();
}

bool CheckBonusEffectEnd(Player & player, DurationController & ctrl, std::vector<json_spirit::Pair>& config) {
	if (ctrl.curr_elapsed_time >= ctrl.max_elapsed_time) {
		ctrl.curr_elapsed_time = 0.f;
		if (ctrl.type == ATK_UP) {
			player.fight->stored_damage = player.fight->damage /= GetConfig(config, "BONUS_VALUE", ATK_UP);
		}
		else if (ctrl.type == SPEED_UP) {
			player.movement->step /= GetConfig(config, "BONUS_VALUE", SPEED_UP);
		}
		return true;
	}
	return false;
}

void CheckDynamicObjCollisions(Game& game) {
	Player& player = *game.player;
	vector<Object> map_objects = game.res->lvl->GetAllObjects();
	list<Enemy*>::iterator list_begin = game.enemy_list->begin();
	list<Enemy*>::iterator list_end = game.enemy_list->end();
	for (list<Bonus*>::iterator iter = game.bonus_list->begin(); iter != game.bonus_list->end(); ++iter) {
		Bonus* bonus = *iter;
		PlayerBonusCollision(player, *bonus);
		if (bonus->bonus_logic->picked_up) {
			PlaySound(BONUS_PICK, *game.game_sounds->sounds, *game.game_sounds->sound_buffers);
			game.dur_ctrl_list->push_back(CreateDurationController(*bonus->bonus_logic));
			DestroyBonus(*bonus);
			game.bonus_list->remove(*iter);
			break;
		}
	}
	for (list<Enemy*>::iterator iter = list_begin; iter != list_end; ++iter) {
		Enemy* enemy = *iter;
		float old_enemy_hp = enemy->fight->health_points;
		PlayerEnemyCollision(player, *enemy);
		if (old_enemy_hp != enemy->fight->health_points) {
			PlaySound(HIT, *game.game_sounds->sounds, *game.game_sounds->sound_buffers);
		}
		float old_player_hp = player.fight->health_points;
		EnemyPlayerCollision(*enemy, player);
		if (old_player_hp != player.fight->health_points) {
			if ((rand() % 6) == 0) {
				PlaySound(GET_HIT, *game.game_sounds->sounds, *game.game_sounds->sound_buffers);
			}
			
		}
		if (player.fight->is_dead) {

			break;
		}
		if (enemy->fight->is_dead) {
			DestroyEnemy(*enemy);
			game.enemy_list->remove(*iter);
			break;

		}
	}
}

void PlayerEnemyCollision(const Player& player, Enemy& enemy) {
	Animation& player_anim = *player.visual->animation;
	FightLogic& enemy_fight = *enemy.fight;
	float& enemy_hp = enemy.fight->health_points;
	FloatRect player_sprite = player.visual->animation->frame->sprite.getGlobalBounds();
	FloatRect& enemy_rect = *enemy.visual->rect;
	float& player_damage = player.fight->damage;
	float& player_stored_damage = player.fight->stored_damage;
	bool is_hit = int(player_anim.current_attack_frame) == 3;
	if (player_sprite.intersects(enemy_rect) && is_hit) {
		enemy.is_attacked = true;
		if (enemy_hp <= 0) {
			enemy_fight.is_dead = true;
			player_damage = player_stored_damage;
		}
		else {
			enemy.visual->animation->is_injured = true;
			enemy_hp -= player_damage;
			player_damage = 0;
		}

	}
	else {
		if (enemy.is_attacked) {
			enemy.is_attacked = false;
			enemy.visual->animation->is_injured = false;
			player_damage = player_stored_damage;
		}

	}
}

void PlayerBonusCollision(const Player& player, Bonus& bonus) {
	FloatRect player_sprite = player.visual->animation->frame->sprite.getGlobalBounds();
	FloatRect bonus_sprite = bonus.bonus_visual->sprite.getGlobalBounds();
	FightLogic& fight = *player.fight;
	Movement& movement = *player.movement;
	if (player_sprite.intersects(bonus_sprite)) {
		bonus.bonus_logic->picked_up = true;
		switch (bonus.bonus_logic->bonus_type) {
			case HP_REGEN:
				fight.health_points += bonus.bonus_logic->value;
				break;
			case SPEED_UP:
				movement.step *= bonus.bonus_logic->value;
				break;
			case ATK_UP:
				fight.stored_damage = fight.damage *= bonus.bonus_logic->value;
				break;
		}
	}

}

void EnemyPlayerCollision(const Enemy& enemy, Player& player) {
	Animation& enemy_anim = *enemy.visual->animation;
	FightLogic& player_fight = *player.fight;
	float& player_hp = player.fight->health_points;
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
			player.visual->animation->is_injured = true;
		}
		enemy_damage = 0;
	}
	else {
		if (enemy_damage == 0) {
			player.visual->animation->is_injured = false;
		}
		enemy_damage = CEnemyDamage;
	}
}


void DestroyWindow(RenderWindow& window) {
	delete &window;
}

void DestroyEnemyList(list<Enemy*>& enemy_list) {
	list<Enemy*>::iterator begin = enemy_list.begin();
	list<Enemy*>::iterator end = enemy_list.end();
	for (list<Enemy*>::iterator iter = begin; iter != end; ++iter) {
		DestroyEnemy(**iter);
	}
	delete &enemy_list;
}

void DestroyBonusList(list<Bonus*>& bonus_list) {
	for (Bonus* bonus : bonus_list) {
		DestroyBonus(*bonus);
	}
}

void DestroyGame(Game*& game) {
	DestroyWindow(*game->window);
	DestroyLevel(*game->res->lvl);
	DestroyPlayer(*game->player);
	DestroyEnemyList(*game->enemy_list);
	DestroyBonusList(*game->bonus_list);
	DestroyResourses(*game->res);
	DestroyBonusesPanel(*game->b_panel);
	DestroyGameSounds(*game->game_sounds);
	delete game->view;
	delete game;
}