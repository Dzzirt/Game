#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"


struct Visual {
	Animation*	animation;

	sf::FloatRect* rect;
};

void VisualInit(Visual & visual, Type type, sf::FloatRect & rect);

