#pragma once
#include <SFML/Graphics.hpp>
#include "using_json.h"

struct FrameRects {
	sf::IntRect move;
	sf::IntRect stay;
	sf::IntRect jump;
	sf::IntRect attack;
	sf::IntRect gravity;
};


void FrameRectInit(FrameRects&, Type);
