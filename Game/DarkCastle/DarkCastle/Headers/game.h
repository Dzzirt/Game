#pragma once
#include <list>
#include "player.h"
#include "enemy.h"
#include "bonus.h"
#include "resourses.h"
#include "view.h"
#include "bonuses_panel.h"
#include "duration_controller.h"
#include "SFML/Audio.hpp"
#include <sstream>
#include "mace_traps_utils.h"
#include "die_screen.h"

struct Game {
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
};


Game* CreateGame();

void RestartGame(Game *& game);

void ProcessEnemyListEvents(std::list<Enemy*> & enemy_list, sf::FloatRect & player_rect);

sf::RenderWindow* CreateRenderWindow();

std::list<Enemy*>* CreateEnemyList(Resourses & res);

std::list<Bonus*>* CreateBonusList(Resourses & res);

std::list<DurationController*>* CreateDurationControllerVec();


void GameInit(Game& game);

void BonusListInit(std::list<Bonus*>& bonus_list, Resourses & res, BonusType type);

void EnemyListInit(std::list<Enemy*> & en_list, Resourses & res, Type type);


void ProcessEvents(Game *& game);

void ChangeMap(Game &game, std::string map_name);

void CheckMapChanging(Game &game);

void WoundsCheck(Game &game);

void MaceTrapsVecUpdate(std::vector<MaceTrap*> & traps, const sf::Time& deltaTime);

void DrawEnemies(std::list<Enemy*> & enemies, sf::RenderWindow &window);

void DrawPlayer(Player & player, sf::RenderWindow &window);

void DrawBonuses(std::list<Bonus*> & bonus_list, sf::RenderWindow &window);

void BonusListUpdate(std::list<Bonus*> & bonuses, const sf::Time& deltaTime);

void EnemyListUpdate(std::list<Enemy*> & enemy_list, Level & level, const sf::Time& deltaTime);

void DurationControllersVecUpdate(std::list<DurationController*> & ctrls, const sf::Time& deltaTime);

void Update(Game& game, const sf::Time& deltaTime);

void Render(Game & game);


bool ÑheckingBonusEffectActivation(Game & game);

bool CheckBonusEffectEnd(Player & player, DurationController & ctrl, std::vector<json_spirit::Pair>& config);


void CheckPlayerAndEnemiesCollisions(std::list<Enemy*> & enemy_list, Player& player);

void PickUpBonus(Game &game, Bonus * bonus, std::list<Bonus*>::iterator iter);

void CheckDynamicObjCollisions(Game& game);

void CheckPlayerBonusCollision(const Player& player, Bonus& bonus);

void PlayerEnemyCollision(const Player & player, Enemy & enemy);

void PlayerMaceTrapCollision(Player& player, MaceTrap & trap);

void EnemyPlayerCollision(const Enemy& enemy, Player& player);


void DestroyGame(Game*& game);

void DestroyWindow(sf::RenderWindow& window);

void DestroyBonusList(std::list<Bonus*>& bonus_list);

void DestroyEnemyList(std::list<Enemy*>& enemy_list);
