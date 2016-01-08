#pragma once
#include "consts_and_enums.h"
#include "visual.h"
#include "jump.h"
#include "fight_logic.h"
#include "resourses.h"



struct Player {
	Movement * movement;
	FightLogic * fight;
	HpBar* hp_bar;
	Visual * visual;
	Jump* jumping;
	bool is_map_complete;
	bool is_injured;
};

Player* CreatePlayer(Resourses & res);

void PlayerInit(Player& player, Resourses & res);

void PlayerUpdate(Player & player, Level & level, const sf::Time& deltaTime);

void CheckGravityLogic(Jump & jump, Movement & movement, const sf::Time& deltaTime);

sf::FloatRect GetPlayerRectFromLvl(Level & lvl);

void AnimationsUpdate(Player& player);

void ProcessPlayerEvents(sf::RenderWindow& window,Player & player, GameSounds & sounds, sf::View & view);

void CheckPlayerAndLevelCollision(Player& player, Level& level);

void PlayerLevelCollision(Player & player, const Object & map_object);

void DrawPlayer(Player & player, sf::RenderWindow &window);

void DestroyPlayer(Player*& player);