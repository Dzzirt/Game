#include <sstream>
#include "../Headers/game.h"
#include "../Headers/safe_delete.h"

using namespace sf;
using namespace std;

Game* CreateGame() {
	Game* game = new Game();
	GameInit(*game);
	return game;
}

void GameInit(Game& game) {
	game.state = MAIN_MENU;
	game.menu.button.handler = [&game]()
	{
		game.state = PLAY;
	};
	game.view = CreateView();
	game.res = CreateResourses();
	game.player = CreatePlayer(*game.res);
	game.enemy_list = CreateEnemyList(*game.res);
	game.bonus_list = CreateBonusList(*game.res);
	game.b_panel = CreateBonusesPanel();
	game.dur_ctrl_list = CreateDurationControllerVec();
	game.game_sounds = CreateGameSounds();
	game.die_screen = CreateDieScreen();
	game.win_screen = CreateWinScreen();
	MaceTrapVecInit(game.mace_traps, *game.res->lvl);
}

void RestartGame(Game *& game) {
	DestroyGame(game);
	game = CreateGame();
}

void ProcessGameEvents(Game & game, sf::Event & event, RenderWindow & window)
{
	Level & level = *game.res->lvl;
	View & view = *game.view;
	if (event.type == Event::Closed)
	{
		window.close();
	}
	else if (event.type == Event::Resized)
	{
		view.setSize(float(event.size.width), float(event.size.height));
		int map_height = level.height * level.tileHeight;
		int map_width = level.width * level.tileWidth;
		cout << map_height / float(event.size.height * event.size.height / WindowHeight) << endl;
		if (map_height < map_width)
		{
			if (unsigned(map_height) < event.size.height)
			{
				view.zoom(map_height / float(event.size.height));
			}
		}
		else
		{
			if (unsigned(map_width) < event.size.width)
			{
				view.zoom(unsigned(map_width) / float(event.size.width));
			}
		}
	}
}

void ProcessEvents(Game *& game, RenderWindow & window)
{
	Event event;
	if (game->state == PLAY) {
		ProcessEnemyListEvents(*game->enemy_list, *game->player->visual->rect);
		if (game->player->fight->is_dead)
		{
			game->state = DEAD;
		}
		else if (game->res->lvl->GetAllObjects()->size() == 0)
		{
			game->state = WIN;
		}
	}
	while (window.pollEvent(event))
	{
		ProcessGameEvents(*game, event, window);
		if (game->state == PLAY)
		{
			ProcessPlayerEvents(window, *game->player, *game->game_sounds, *game->view);
			ProcessPanelEvents(*game->b_panel);
		}
		else if (game->state == MAIN_MENU)
		{
			game->menu.ProcessEvents(event);
		}
		else if (game->state == DEAD || game->state == WIN)
		{
			if (Keyboard::isKeyPressed(Keyboard::R))
			{
				RestartGame(game);
			}
		}
	}
}

void ChangeMap(Game &game, std::string map_name) {
	DestroyLevel(game.res->lvl);
	DestroyBonusList(game.bonus_list);
	DestroyEnemyList(game.enemy_list);
	DestroyMaceTrapVec(game.mace_traps);
	if (map_name == "map3.tmx")
	{
		game.game_sounds->bg_sound.openFromFile("Resourses/Sounds/bg_peacefull.ogg");
		game.game_sounds->bg_sound.setLoop(true);
		game.game_sounds->bg_sound.setVolume(BGMusicVolume);
		game.game_sounds->bg_sound.play();
	}
	game.res->lvl = CreateLevel("Resourses/Maps/" + map_name);
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

void Update(Game& game, const Time& deltaTime) {
	if (game.state == PLAY)
	{
		PlayerUpdate(*game.player, *game.res->lvl, deltaTime);
		CheckMapChanging(game);
		ViewUpdate(*game.view, *game.player->movement, *game.res->lvl, game.player->visual->animation->frame->displacement);
		HpBarUpdate(*game.player->hp_bar, *game.view, game.player->fight->health_points);
		BonusesPanelUpdate(*game.b_panel, *game.view);
		ÑheckingBonusEffectActivation(game);
		MaceTrapsVecUpdate(game.mace_traps, TimePerFrame);
		BonusListUpdate(*game.bonus_list, deltaTime);
		EnemyListUpdate(*game.enemy_list, *game.res->lvl, deltaTime, *game.view);
		DurationControllersVecUpdate(*game.dur_ctrl_list, deltaTime);
		for (DurationController *& ctrl : *game.dur_ctrl_list)
		{
			if (CheckBonusEffectEnd(*game.player, *ctrl, *game.res->config))
			{
				DestroyDurationController(ctrl);
				game.dur_ctrl_list->remove(ctrl);
				break;
			}
		}
		CheckDynamicObjCollisions(game);
		WoundsCheck(game);
	}
}

void Render(Game & game, RenderWindow & window) {
	window.clear();
	if (game.state == PLAY)
	{
			game.res->lvl->Draw(window);
			window.setView(*game.view);
			DrawBonuses(*game.bonus_list, window);
			DrawPlayer(*game.player, window);
			DrawEnemies(*game.enemy_list, window);
			DrawBonusesPanel(*game.b_panel, window);
			DrawMaceTraps(game.mace_traps, window);
	}
	else if (game.state == MAIN_MENU)
	{
		game.menu.Draw(window);
	}
	else if (game.state == DEAD)
	{
		game.view->setCenter(WindowWidth / 2.f, WindowHeight / 2.f);
		window.setView(*game.view);
		DrawDieScreen(*game.die_screen, window);
	}
	else if (game.state == WIN)
	{
		game.view->setCenter(WindowWidth / 2.f, WindowHeight / 2.f);
		window.setView(*game.view);
		DrawWinScreen(*game.win_screen, window);
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
			DestroyCell(items[i]);
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

void PickUpBonus(Game &game, std::list<Bonus*>::iterator iter) {
	Bonus * bonus = *iter;
	if (AddToItemsVec(*game.b_panel->items, **iter)) {
		PlaySounds(BONUS_PICK, *game.game_sounds->sounds, *game.game_sounds->sound_buffers);
		game.bonus_list->remove(*iter);
		DestroyBonus(bonus);
	}
	else {
		bonus->bonus_logic->picked_up = false;
	}
}

void CheckDynamicObjCollisions(Game& game) {
	Player& player = *game.player;
	for (Bonus * bonus : *game.bonus_list) {
		CheckPlayerBonusCollision(player, *bonus);
	}
	list<Bonus*>::iterator bonus_list_begin = game.bonus_list->begin();
	list<Bonus*>::iterator bonus_list_end = game.bonus_list->end();
	for (list<Bonus*>::iterator iter = bonus_list_begin; iter != bonus_list_end; ++iter) {
		Bonus * bonus = *iter;
		if (bonus->bonus_logic->picked_up) {
			PickUpBonus(game, iter);
			break;
		}
	}
	for (MaceTrap* mace_trap : game.mace_traps) {
		PlayerMaceTrapCollision(player, *mace_trap);
	}
	CheckPlayerAndEnemiesCollisions(*game.enemy_list, player);

}

void DestroyGame(Game*& game) {
	DestroyPlayer(game->player);
	DestroyEnemyList(game->enemy_list);
	DestroyBonusList(game->bonus_list);
	DestroyDurationControllerVec(game->dur_ctrl_list);
	DestroyResourses(game->res);
	DestroyBonusesPanel(game->b_panel);
	DestroyGameSounds(game->game_sounds);
	DestroyMaceTrapVec(game->mace_traps);
	DestroyDieScreen(game->die_screen);
	DestroyView(game->view);
	SafeDelete(game);
}