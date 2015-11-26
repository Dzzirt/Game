#pragma once
#include "SFML/Graphics.hpp"
#include "consts_and_enums.h"
#include "using_json.h"

struct BonusVisual {
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
};


BonusVisual* CreateBonusVisual(BonusType type);

void BonusVisualInit(BonusVisual & bonus_visual, BonusType type);

void DestroyBonusVisual(BonusVisual & bonus_visual);