#include "../Headers/main_menu.h"

MainMenu::MainMenu()
{
	bg_texture.loadFromFile("Resourses/Screens/dark_castle.png");
	bg.setTexture(bg_texture);
	button.Init();
	button.SetPosition(sf::Vector2f(99.f, 325.f));
}

void MainMenu::Draw(sf::RenderWindow & window)
{
	window.draw(bg);
	button.Draw(window);
}

void MainMenu::ProcessEvents(const sf::Event & event)
{
	button.OnEvent(event);
}
