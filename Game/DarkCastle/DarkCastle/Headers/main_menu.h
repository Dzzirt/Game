#include "SFML/Graphics.hpp"
#include "button.h"

struct MainMenu
{
	sf::Sprite bg;
	sf::Texture bg_texture;
	StartGameButton button;

	MainMenu();
	void Draw(sf::RenderWindow & window);
	void ProcessEvents(const sf::Event & event);

};