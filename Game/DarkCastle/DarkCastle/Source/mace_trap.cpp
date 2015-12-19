#include "../Headers/mace_trap.h"
#include <iostream>
#include "../Headers/safe_delete.h"


MaceTrap* CreateMaceTrap() {
	MaceTrap* mace_trap = new MaceTrap();
	MaceTrapInit(*mace_trap);
	return mace_trap;
}

void MaceTrapInit(MaceTrap & mace_trap) {
	mace_trap.texture.loadFromFile("Resourses/Traps/mace_trap.png");
	mace_trap.texture.setSmooth(true);
	mace_trap.sprite.setTexture(mace_trap.texture);
	mace_trap.speed = 0.f;
	mace_trap.rotation = -70;
	mace_trap.damage = MaceTrapDamage;
	mace_trap.sprite.setRotation(-70.f);
	mace_trap.sprite.setOrigin(20, 0);
}

void MaceTrapUpdate(MaceTrap & mace_trap, const sf::Time& deltaTime) {
	if (mace_trap.rotation < 0) {
		mace_trap.speed += MaceTrapSpeed * deltaTime.asSeconds();
	}
	else {
		mace_trap.speed -= MaceTrapSpeed * deltaTime.asSeconds();
	}
	mace_trap.sprite.setRotation(mace_trap.rotation + mace_trap.speed);
	mace_trap.rotation += mace_trap.speed;
}


void DestroyMaceTrap(MaceTrap *& mace_trap) {
	SafeDelete(mace_trap);
}

