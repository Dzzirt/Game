#pragma once
#include "bonuses_panel_const.h"
#include  "SFML/Graphics.hpp"
#include "bonus.h"

struct BonusesPanel {
	std::vector<Bonus*>* items;
	sf::Image img;
	sf::Texture texture;
	sf::Sprite sprite;
};

BonusesPanel* CreateBonusesPanel();

void BonusesPanelInit(BonusesPanel & panel);

std::vector<Bonus*>* CreateItemsVec();

void DestroyBonusesPanel(BonusesPanel & panel);

void DrawBonusesPanel(BonusesPanel & panel, sf::RenderWindow & window);

void BonusesPanelUpdate(BonusesPanel & panel, sf::View view);