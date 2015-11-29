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

FrameRects* CreateFrameRects(Type type, std::vector<json_spirit::Pair> & int_rects);

void FrameRectInit(FrameRects&, Type, std::vector<json_spirit::Pair> & int_rects);

void DestroyFrameRects(FrameRects *& frame_rects);