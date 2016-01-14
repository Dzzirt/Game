#pragma once
#include "view.h"
#include "bonuses_panel.h"
#include "SFML/Audio.hpp"
#include "mace_traps_utils.h"
#include "die_screen.h"
#include "enemy_list_utils.h"
#include "bonus_list_utils.h"
#include "collision_utils.h"
#include "duration_vec_utils.h"
#include "main_menu.h"
#include "win_screen.h"

enum GameState
{
	MAIN_MENU,
	PLAY,
	DEAD,
	WIN
};

struct Game {
	GameState state;
	Player* player;
	Resourses* res;
	BonusesPanel* b_panel;
	GameSounds* game_sounds;
	std::vector<MaceTrap*> mace_traps;
	std::list<Enemy*> * enemy_list;
	std::list<Bonus*> * bonus_list;
	std::list<DurationController*> * dur_ctrl_list;
	DieScreen * die_screen;
	sf::View* view;
	MainMenu menu;
	WinScreen * win_screen;

};


Game* CreateGame();

void RestartGame(Game *& game);

void ProcessGameEvents(Game & game, sf::Event & event, sf::RenderWindow & window);

void GameInit(Game& game);

void ProcessEvents(Game *& game, sf::RenderWindow & window);

void ChangeMap(Game &game, std::string map_name);

void CheckMapChanging(Game &game);

void WoundsCheck(Game &game);

void Update(Game& game, const sf::Time& deltaTime);

void Render(Game & game, sf::RenderWindow & window);

bool ÑheckingBonusEffectActivation(Game & game);

bool CheckBonusEffectEnd(Player & player, DurationController & ctrl, std::vector<json_spirit::Pair>& config);

void PickUpBonus(Game &game, std::list<Bonus*>::iterator iter);

void CheckDynamicObjCollisions(Game& game);

void DestroyGame(Game*& game);

