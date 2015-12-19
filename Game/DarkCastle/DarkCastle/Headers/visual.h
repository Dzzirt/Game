#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"


struct Visual {
	Animation*	animation;

	sf::FloatRect* rect;
};

Visual* CreateVisual(Type type, sf::FloatRect & rect, std::vector<json_spirit::Pair> & int_rects);

void VisualInit(Visual & visual, Type type, sf::FloatRect & rect, std::vector<json_spirit::Pair> & int_rects);

void DestroyVisual(Visual *& visual);
