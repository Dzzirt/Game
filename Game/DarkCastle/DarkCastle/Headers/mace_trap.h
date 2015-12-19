#pragma once
#include "SFML/Graphics.hpp"

const float MaceTrapDamage = 30.f;
const float MaceTrapSpeed = 3.f;

struct MaceTrap {
  sf::Texture texture;
	sf::Sprite sprite;
	float rotation;
	float speed;
	float damage;
};


MaceTrap* CreateMaceTrap();

void MaceTrapInit(MaceTrap & mace_trap);

void DestroyMaceTrap(MaceTrap *& mace_trap);

void MaceTrapUpdate(MaceTrap & mace_trap, const sf::Time& deltaTime);
