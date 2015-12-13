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

struct Game {
	Player* player;
	Resourses* res;
	BonusesPanel* b_panel;
	GameSounds* game_sounds;
	std::list<Enemy*> * enemy_list;
	std::list<Bonus*> * bonus_list;
	std::list<DurationController*> * dur_ctrl_list;
	sf::RenderWindow * window;
	sf::View* view;
};


Game* CreateGame();

void RestartGame(Game *& game);

sf::RenderWindow* CreateRenderWindow();

std::list<Enemy*>* CreateEnemyList(Resourses & res);

std::list<Bonus*>* CreateBonusList(Resourses & res);

std::list<DurationController*>* CreateDurationControllerVec();


void GameInit(Game& game);

void BonusListInit(std::list<Bonus*>& bonus_list, Resourses & res, BonusType type);

void EnemyListInit(std::list<Enemy*> & en_list, Resourses & res, Type type);


void ProcessEvents(Game *& game);

void Update(Game& game, const sf::Time& deltaTime);

void Render(Game & game);


bool ÑheckingBonusEffectActivation(Game & game);

bool CheckBonusEffectEnd(Player & player, DurationController & ctrl, std::vector<json_spirit::Pair>& config);


void CheckDynamicObjCollisions(Game& game);

void PlayerBonusCollision(const Player& player, Bonus& bonus);

void PlayerEnemyCollision(const Player & player, Enemy & enemy);

void EnemyPlayerCollision(const Enemy& enemy, Player& player);


void DestroyGame(Game*& game);

void DestroyWindow(sf::RenderWindow& window);

void DestroyBonusList(std::list<Bonus*>& bonus_list);

void DestroyEnemyList(std::list<Enemy*>& enemy_list);
