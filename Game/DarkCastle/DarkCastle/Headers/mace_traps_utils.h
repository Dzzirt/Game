#pragma once
#include "mace_trap.h"
#include "level.hpp"
#include <sstream>


const float DecreaseMaceSize = 20.f;

const float DisplaceMace = 20.f;

void MaceTrapVecInit(std::vector<MaceTrap*> & mace_traps, Level & level);

int GetMaceTrapsCount(Level& lvl);

sf::Vector2f GetMaceTrapPosFromLvl(Level & level, int number);

void DrawMaceTraps(std::vector<MaceTrap*> & mace_traps, sf::RenderWindow & window);

void DestroyMaceTrapVec(std::vector<MaceTrap*> & mace_traps);
