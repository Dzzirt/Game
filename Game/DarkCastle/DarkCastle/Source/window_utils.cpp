#include "../Headers/window_utils.h"
#include "../Headers/consts_and_enums.h"
#include "../Headers/safe_delete.h"

using namespace sf;

RenderWindow* CreateRenderWindow()
{
	return new RenderWindow(VideoMode(WindowWidth, WindowHeight), "Dark Castle");
}

void DestroyWindow(sf::RenderWindow *& window)
{
	SafeDelete(window);
}