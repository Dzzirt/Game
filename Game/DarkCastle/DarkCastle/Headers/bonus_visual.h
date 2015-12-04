#pragma once
#include "SFML/Graphics.hpp"
#include "consts_and_enums.h"
#include "using_json.h"

struct BonusVisual {
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect sprite_rect;
};


BonusVisual* CreateBonusVisual(BonusType type, std::vector<json_spirit::Pair> & int_rects);

void BonusVisualInit(BonusVisual & bonus_visual, BonusType type, std::vector<json_spirit::Pair> & int_rects);

void DestroyBonusVisual(BonusVisual & bonus_visual);