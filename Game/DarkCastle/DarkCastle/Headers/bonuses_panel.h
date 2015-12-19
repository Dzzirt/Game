#pragma once
#include "bonuses_panel_const.h"
#include  "SFML/Graphics.hpp"
#include "cell.h"

struct BonusesPanel {
	std::vector<Cell*>* items;
	sf::Image img;
	sf::Texture texture;
	sf::Sprite sprite;
};

BonusesPanel* CreateBonusesPanel();

void BonusesPanelInit(BonusesPanel & panel);

std::vector<Cell*>* CreateItemsVec();

bool AddToItemsVec(std::vector<Cell*> & items, Bonus & bonus);

void DestroyItemsVec(std::vector<Cell*> *& items); 

void DestroyBonusesPanel(BonusesPanel *& panel);

void BonusesPanelUpdate(BonusesPanel & panel, sf::View view);

void ProcessPanelEvents(BonusesPanel& panel);

void DrawBonusesPanel(BonusesPanel & panel, sf::RenderWindow & window);