#pragma once
#include <SFML/Graphics.hpp>

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

enum State {
	LEFT,
	RIGHT,
	NONE
};