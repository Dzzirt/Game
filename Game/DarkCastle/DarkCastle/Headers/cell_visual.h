#pragma once
#include "SFML/Graphics.hpp"
#include "bonus_visual.h"


struct CellVisual {
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect sprite_rect;
};

CellVisual* CreateCellVisual(BonusVisual & b_visual);

void CellVisualInit(CellVisual & cell_visual, BonusVisual & b_visual);

void DestroyCellVisual(CellVisual & cell_visual);