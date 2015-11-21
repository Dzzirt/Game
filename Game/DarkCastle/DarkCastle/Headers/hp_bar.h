#pragma once
#include <SFML/Graphics.hpp>
#include "consts_and_enums.h"


struct HpBar {
	sf::Texture bar_texture;
	sf::Sprite bar_sprite;
	sf::Sprite strip_sprite;
	sf::IntRect strip_rect;
	sf::IntRect bar_rect;
};

void HpBarInit(HpBar & hp, Type type);

void DestroyHpBar(HpBar *& hp);