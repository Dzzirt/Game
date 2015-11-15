#pragma once
#include "consts_and_enums.h"
#include "visual.h"
#include "jump.h"
#include "logic.h"
#include "level.hpp"


struct Player {
	Logic * logic;
	Visual * visual;
	Jump* jumping;
	sf::View* view;
};

// Player* CreatePlayer();

// DeletePlayer(Player);

void PlayerInit(Player & player, sf::FloatRect & rect);

void PlayerUpdate(Player & player, const Level & level, const sf::Time& deltaTime);

void CheckGravityLogic(Jump & jump, Movement & movement, const sf::Time& deltaTime);

void PlayerLevelCollision(Player & player, const Object & map_object);

sf::FloatRect GetPlayerRectFromLvl(Level & lvl);

void AnimationsUpdate(Player& player);

void ViewUpdate(sf::View& view, sf::RenderWindow & window, const Movement & movement, const Level & level, float displacement);

void ProcessPlayerEvents(sf::RenderWindow& window, Player & player);

void CheckPlayerAndLevelCollision(Player & player, Level & level);
