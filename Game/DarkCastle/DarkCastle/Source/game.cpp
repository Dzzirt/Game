#include <sstream>
#include "../Headers/game.h"

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
	game.opacity = 0;
	game.window = CreateRenderWindow();
	game.view = CreateView();
	game.res = CreateResourses();
	game.player = CreatePlayer(*game.res);
	game.enemy_list = CreateEnemyList(*game.res);
	game.bonus_list = CreateBonusList(*game.res);
	game.b_panel = CreateBonusesPanel();
	game.dur_ctrl_list = CreateDurationControllerVec();
	game.game_sounds = CreateGameSounds();
	game.die_screen = CreateDieScreen();
	MaceTrapVecInit(game.mace_traps, *game.res->lvl);
}


void RestartGame(Game *& game) {
	DestroyGame(game);
	game = CreateGame();
}

void ProcessEnemyListEvents(Game*& game) {
	for (list<Enemy*>::iterator iter = game->enemy_list->begin(); iter != game->enemy_list->end(); ++iter) {
		Enemy* enemy = *iter;
		ProcessEnemyEvents(*enemy, *game->player->visual->rect);
	}
}

void ProcessEvents(Game*& game) {
	RenderWindow& window = *game->window;
	Event event;
	ProcessEnemyListEvents(game);
	while (window.pollEvent(event)) {
		ProcessPlayerEvents(window, event, *game->player, *game->game_sounds, *game->res->lvl, *game->view);
		ProcessPanelEvents(*game->b_panel);
		if (Keyboard::isKeyPressed(Keyboard::R) && game->player->fight->is_dead) {
			RestartGame(game);
		}
	}
}

void ChangeMap(Game &game, std::string map_name) {
	DestroyLevel(*game.res->lvl);
	DestroyBonusList(*game.bonus_list);
	DestroyEnemyList(*game.enemy_list);
	DestroyMaceTrapVec(game.mace_traps);
	game.res->lvl = CreateLevel(map_name);
	*game.player->visual->rect = GetPlayerRectFromLvl(*game.res->lvl);
	game.enemy_list = CreateEnemyList(*game.res);
	game.bonus_list = CreateBonusList(*game.res);
	MaceTrapVecInit(game.mace_traps, *game.res->lvl);
}

void CheckMapChanging(Game &game) {
	if (game.player->is_map_complete) {
		stringstream name;
		game.res->curr_lvl_num++;
		name << game.res->curr_lvl_num;
		ChangeMap(game, "map" + name.str() + ".tmx");
		game.player->is_map_complete = false;
	}
}

void WoundsCheck(Game &game) {
	if (game.player->is_injured) {
		if ((rand() % 6) == 0) {
			PlaySounds(GET_HIT, *game.game_sounds->sounds, *game.game_sounds->sound_buffers);
		}
		game.player->visual->animation->frame->sprite.setColor(Color::Red);
		game.player->is_injured = false;
	}
	for (Enemy * enemy : *game.enemy_list) {
		if (enemy->is_injured) {
			PlaySounds(HIT, *game.game_sounds->sounds, *game.game_sounds->sound_buffers);
			enemy->visual->animation->frame->sprite.setColor(Color::Red);
			enemy->is_injured = false;
		}
	}
}

void MaceTrapsVecUpdate(std::vector<MaceTrap*> & traps, const Time& deltaTime) {
	for (MaceTrap* trap : traps) {
		MaceTrapUpdate(*trap, deltaTime);
	}
}

void BonusListUpdate(std::list<Bonus*> & bonuses, const Time& deltaTime) {
	for (Bonus * bonus : bonuses) {
		BonusUpdate(*bonus, deltaTime);
	}
}

void EnemyListUpdate(std::list<Enemy*> & enemy_list, Level & level, const Time& deltaTime) {
	for (Enemy * enemy : enemy_list) {
		EnemyUpdate(*enemy, deltaTime, level);
	}
}

void DurationControllersVecUpdate(std::list<DurationController*> & ctrls, const Time& deltaTime) {
	for (DurationController *& ctrl : ctrls) {
		DuratonControllerUpdate(*ctrl, deltaTime);
	}
}

void Update(Game& game, const Time& deltaTime) {
	PlayerUpdate(*game.player, *game.res->lvl, deltaTime);
	CheckMapChanging(game);
	ViewUpdate(*game.view, *game.player->movement, *game.res->lvl, game.player->visual->animation->frame->displacement);
	HpBarUpdate(*game.player->hp_bar, *game.view, game.player->fight->health_points);
	BonusesPanelUpdate(*game.b_panel, *game.view);
	ÑheckingBonusEffectActivation(game);
	MaceTrapsVecUpdate(game.mace_traps, TimePerFrame);
	BonusListUpdate(*game.bonus_list, deltaTime);
	EnemyListUpdate(*game.enemy_list, *game.res->lvl, deltaTime);
	DurationControllersVecUpdate(*game.dur_ctrl_list, deltaTime);
	for (DurationController *& ctrl : *game.dur_ctrl_list) {
		if (CheckBonusEffectEnd(*game.player, *ctrl, *game.res->config)) {
			DestroyDurationController(*ctrl);
			game.dur_ctrl_list->remove(ctrl);
			break;
		}
	}
	CheckDynamicObjCollisions(game);
	WoundsCheck(game);

}


void DrawEnemies(std::list<Enemy*> & enemies, RenderWindow &window) {
	for (list<Enemy*>::iterator iter = enemies.begin(); iter != enemies.end(); ++iter) {
		Enemy* enemy = *iter;
		VisualHpBar& enemy_hp = *enemy->hp_bar->visual_hp;
		Sprite& enemy_sprite = enemy->visual->animation->frame->sprite;
		window.draw(enemy_sprite);
		window.draw(enemy_hp.bar_sprite);
		window.draw(enemy_hp.strip_sprite);
	}
}

void DrawPlayer(Player & player, RenderWindow &window) {
	VisualHpBar& player_hp = *player.hp_bar->visual_hp;
	Sprite& player_sprite = player.visual->animation->frame->sprite;
	window.draw(player_sprite);
	window.draw(player_hp.bar_sprite);
	window.draw(player_hp.strip_sprite);
}

void DrawBonuses(std::list<Bonus*> & bonus_list, RenderWindow &window) {
	for (list<Bonus*>::iterator iter = bonus_list.begin(); iter != bonus_list.end(); ++iter) {
		Bonus* bonus = *iter;
		window.draw(bonus->bonus_visual->sprite);
	}
}

void Render(Game& game) {
	RenderWindow& window = *game.window;
	window.clear();
	if (game.player->fight->is_dead) {
		game.view->setCenter(WindowWidth / 2.f, WindowHeight / 2.f);
		window.setView(*game.view);
		DrawDieScreen(*game.die_screen, window);
	}
	else {
		game.res->lvl->Draw(window);
		window.setView(*game.view);
		DrawBonuses(*game.bonus_list, window);
		DrawPlayer(*game.player, window);
		DrawEnemies(*game.enemy_list, window);
		DrawBonusesPanel(*game.b_panel, window);
		DrawMaceTraps(game.mace_traps, window);
	}
	window.display();
}

bool ÑheckingBonusEffectActivation(Game & game) {
	FightLogic& fight = *game.player->fight;
	std::vector<Cell*> & items = *game.b_panel->items;
	GameSounds & game_sounds = *game.game_sounds;
	list<DurationController*> & dur_ctrl_list = *game.dur_ctrl_list;
	Movement& movement = *game.player->movement;
	for (size_t i = 0; i < items.size(); i++) {
		if (items[i]->logic->is_activated) {
			PlaySounds(BONUS_PICK, *game_sounds.sounds, *game_sounds.sound_buffers);
			items[i]->logic->is_activated = false;
			switch (items[i]->logic->type) {
			case HP_REGEN:
				fight.health_points += items[i]->logic->value;
				if (fight.health_points > fight.max_health_points) {
					fight.health_points = fight.max_health_points;
				}
				break;
			case SPEED_UP:
				movement.step *= items[i]->logic->value;
				break;
			case ATK_UP:
				fight.stored_damage = fight.damage *= items[i]->logic->value;
				break;
			}
			dur_ctrl_list.push_back(CreateDurationController(*items[i]->logic));
			DestroyCell(*items[i]);
			items.erase(items.begin() + i);
			return true;
		}
	}
	return false;
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
			if (AddToItemsVec(*game.b_panel->items, *bonus)) {
				PlaySounds(BONUS_PICK, *game.game_sounds->sounds, *game.game_sounds->sound_buffers);
				game.bonus_list->remove(*iter);
				DestroyBonus(*bonus);
			}
			else {
				bonus->bonus_logic->picked_up = false;
			}
			break;
		}
	}
	for (MaceTrap* mace_trap : game.mace_traps) {
		PlayerMaceTrapCollision(player, *mace_trap);
	}
	for (list<Enemy*>::iterator iter = list_begin; iter != list_end; ++iter) {
		Enemy* enemy = *iter;
		float old_enemy_hp = enemy->fight->health_points;
		PlayerEnemyCollision(player, *enemy);
		float old_player_hp = player.fight->health_points;
		EnemyPlayerCollision(*enemy, player);
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
			enemy_hp -= player_damage;
			player_damage = 0;
			enemy.is_injured = true;
		}

	}
	else {
		if (enemy.is_attacked) {
			enemy.is_attacked = false;
			player_damage = player_stored_damage;
		}

	}
}


void PlayerMaceTrapCollision(Player& player, MaceTrap & trap) {
	FloatRect player_sprite = player.visual->animation->frame->sprite.getGlobalBounds();
	FloatRect mace_sprite = trap.sprite.getGlobalBounds();
	mace_sprite.left += DisplaceMace;
	mace_sprite.width -= DecreaseMaceSize;
	mace_sprite.height -= DecreaseMaceSize;
	float& player_hp = player.fight->health_points;
	FightLogic& player_fight = *player.fight;
	if (player_sprite.intersects(mace_sprite)) {
		if (player_hp <= 0) {
			player_fight.is_dead = true;
		}
		else {
			player_hp -= trap.damage;
			player.visual->animation->frame->sprite.setColor(Color::Red);
			trap.damage = 0;
		}
	}
	else {
		trap.damage = MaceTrapDamage;
	}
}

void PlayerBonusCollision(const Player& player, Bonus& bonus) {
	FloatRect player_sprite = player.visual->animation->frame->sprite.getGlobalBounds();
	FloatRect bonus_sprite = bonus.bonus_visual->sprite.getGlobalBounds();
	if (player_sprite.intersects(bonus_sprite)) {
		bonus.bonus_logic->picked_up = true;
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
			player.is_injured = true;
			//player.visual->animation->frame->sprite.setColor(Color::Red);
			enemy_damage = 0;
		}

	}
	else {
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
	delete &bonus_list;
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