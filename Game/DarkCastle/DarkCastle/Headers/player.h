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

};

Player* CreatePlayer(Resourses & res);

void PlayerInit(Player& player, Resourses & res);

void PlayerUpdate(Player & player, const Level & level, const sf::Time& deltaTime);

void CheckGravityLogic(Jump & jump, Movement & movement, const sf::Time& deltaTime);

sf::FloatRect GetPlayerRectFromLvl(Level & lvl);

void AnimationsUpdate(Player& player);

void ProcessPlayerEvents(sf::RenderWindow& window, sf::Event & event, Player & player, GameSounds & sounds, Level & level, sf::View & view);

void CheckPlayerAndLevelCollision(Player& player, const Level& level);

void PlayerLevelCollision(Player & player, const Object & map_object);

void DestroyPlayer(Player& player);