#pragma once
#include "SFML/Graphics.hpp"
#include "level.hpp"
#include "movement.h"


sf::View* CreateView();

void ViewUpdate(sf::View& view, const Movement& movement, const Level& level, float displacement);

void DestroyView(sf::View *& view);