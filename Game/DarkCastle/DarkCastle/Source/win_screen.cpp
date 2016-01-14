#include "../Headers/win_screen.h"
#include "../Headers/safe_delete.h"


WinScreen* CreateWinScreen()
{
	WinScreen* Win_screen = new WinScreen();
	WinScreenInit(*Win_screen);
	return Win_screen;
}

void WinScreenInit(WinScreen & screen)
{
	screen.texture.loadFromFile("Resourses/Screens/win_game.png");
	screen.sprite.setTexture(screen.texture);
}

void DrawWinScreen(WinScreen & screen, sf::RenderWindow & window)
{
	window.draw(screen.sprite);
}

void DestroyWinScreen(WinScreen *& Win_screen)
{
	SafeDelete(Win_screen);
}