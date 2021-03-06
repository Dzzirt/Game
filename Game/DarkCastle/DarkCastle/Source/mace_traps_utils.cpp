#include "../Headers/mace_traps_utils.h"



void MaceTrapVecInit(std::vector<MaceTrap*> & mace_traps, Level & level) {
	for (int i = 0; i < GetMaceTrapsCount(level) ; i++)
	{
		MaceTrap * mace_trap = new MaceTrap();
		MaceTrapInit(*mace_trap);
		mace_trap->sprite.setPosition(GetMaceTrapPosFromLvl(level, i));
		mace_traps.push_back(mace_trap);
	}
}

void MaceTrapsVecUpdate(std::vector<MaceTrap*> & traps, const sf::Time& deltaTime)
{
	for (MaceTrap* trap : traps)
	{
		MaceTrapUpdate(*trap, deltaTime);
	}
}

int GetMaceTrapsCount(Level& lvl) {
		return lvl.GetMatchObjects(0, 9, "MACE_TRAP").size();
}

sf::Vector2f GetMaceTrapPosFromLvl(Level & level, int number) {
	sf::FloatRect rect = level.GetObject("MACE_TRAP" + std::to_string(number)).rect;
	return sf::Vector2f(rect.left, rect.top);
}

void DrawMaceTraps(std::vector<MaceTrap*> & mace_traps, sf::RenderWindow & window) {
	for (MaceTrap* trap : mace_traps) {
		window.draw(trap->sprite);
	}
}

void DestroyMaceTrapVec(std::vector<MaceTrap*> & mace_traps) {
	for_each(mace_traps.begin(), mace_traps.end(), DestroyMaceTrap);
	mace_traps.clear();
}
