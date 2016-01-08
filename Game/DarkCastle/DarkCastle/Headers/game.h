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
#include "../Headers/main_menu.h"

enum GameState
{
	MAIN_MENU,
	PLAY,
	END_GAME
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
	sf::RenderWindow * window;
	DieScreen * die_screen;
	sf::View* view;
	MainMenu menu;
};


Game* CreateGame();

void RestartGame(Game *& game);

void ProcessGameEvents(Game & game, sf::Event & event);

sf::RenderWindow* CreateRenderWindow();

void GameInit(Game& game);

void ProcessEvents(Game *& game);

void ChangeMap(Game &game, std::string map_name);

void CheckMapChanging(Game &game);

void WoundsCheck(Game &game);

void Update(Game& game, const sf::Time& deltaTime);

void Render(Game & game);

bool ÑheckingBonusEffectActivation(Game & game);

bool CheckBonusEffectEnd(Player & player, DurationController & ctrl, std::vector<json_spirit::Pair>& config);

void PickUpBonus(Game &game, std::list<Bonus*>::iterator iter);

void CheckDynamicObjCollisions(Game& game);

void DestroyGame(Game*& game);

void DestroyWindow(sf::RenderWindow *& window);
