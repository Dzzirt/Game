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
	sf::View* view;
};

Player* CreatePlayer(Resourses & res);

sf::View* CreateView(); // колхоз

void DestroyPlayer(Player*& player);

void PlayerInit(Player& player, Resourses & res);

void PlayerUpdate(Player & player, const Level & level, const sf::Time& deltaTime);

void CheckGravityLogic(Jump & jump, Movement & movement, const sf::Time& deltaTime);

void PlayerLevelCollision(Player & player, const Object & map_object);

sf::FloatRect GetPlayerRectFromLvl(Level & lvl);

void AnimationsUpdate(Player& player);

void ViewUpdate(sf::View& view, sf::RenderWindow & window, const Movement & movement, const Level & level, float displacement);

void ProcessPlayerEvents(sf::RenderWindow& window, Player & player, Level & level);

void CheckPlayerAndLevelCollision(Player& player, const Level& level);
