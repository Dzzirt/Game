#pragma once
#include "mace_trap.h"
#include "level.hpp"
#include <sstream>


void MaceTrapVecInit(std::vector<MaceTrap*> & mace_traps, Level & level);

void MaceTrapsVecUpdate(std::vector<MaceTrap*> & traps, const sf::Time& deltaTime);

int GetMaceTrapsCount(Level& lvl);

sf::Vector2f GetMaceTrapPosFromLvl(Level & level, int number);

void DrawMaceTraps(std::vector<MaceTrap*> & mace_traps, sf::RenderWindow & window);

void DestroyMaceTrapVec(std::vector<MaceTrap*> & mace_traps);
