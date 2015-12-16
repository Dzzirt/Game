#include "../Headers/die_screen.h"



DieScreen* CreateDieScreen() {
	DieScreen* die_screen = new DieScreen();
	DieScreenInit(*die_screen);
	return die_screen;
}

void DieScreenInit(DieScreen & screen) {
	screen.texture.loadFromFile("Resourses/die_msg.png");
	screen.sprite.setTexture(screen.texture);
}

void DrawDieScreen(DieScreen & screen, sf::RenderWindow & window) {
	window.draw(screen.sprite);
}
