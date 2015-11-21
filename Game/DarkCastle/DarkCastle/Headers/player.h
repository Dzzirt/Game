#pragma once
#include "consts_and_enums.h"
#include "visual.h"
#include "jump.h"
#include "fight_logic.h"
#include "level.hpp"



struct Player {
	Movement * movement;
	FightLogic * fight;
	Visual * visual;
	Jump* jumping;
	sf::View* view;
};

// Player* CreatePlayer();

// DeletePlayer(Player);

Player* CreatePlayer(Level & level);

void DestroyPlayer(Player*& player);

void PlayerInit(Player & player, Level & level);

void PlayerUpdate(Player & player, const Level & level, const sf::Time& deltaTime);

void CheckGravityLogic(Jump & jump, Movement & movement, const sf::Time& deltaTime);

void PlayerLevelCollision(Player & player, const Object & map_object);

sf::FloatRect GetPlayerRectFromLvl(Level & lvl);

void AnimationsUpdate(Player& player);

void ViewUpdate(sf::View& view, sf::RenderWindow & window, const Movement & movement, const Level & level, float displacement);

void ProcessPlayerEvents(sf::RenderWindow& window, Player & player, Level & level);

void CheckPlayerAndLevelCollision(Player & player, Level & level);
