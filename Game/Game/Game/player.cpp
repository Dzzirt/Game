#include "map.h"
#include "player.h"

using namespace sf;

void ViewInit(sf::View*& view) {
	view = new sf::View();
	view->reset(sf::FloatRect(0, 0, ViewWidth, ViewHeight));
}

void GetPlayerCoordinateForView(sf::View& view, float x, float y) {
	float left_right_border = view.getSize().x / 2;
	float up_down_border = view.getSize().y / 2;
	float tempX = x;
	float tempY = y;

	// Left border collision
	if (x < left_right_border) tempX = left_right_border;

	// Down border collision
	if (y > MapHeight * MapTextureSize - up_down_border) tempY = MapHeight * MapTextureSize - up_down_border;

	// Right border collision
	if (x > MapWidth * MapTextureSize - left_right_border) tempX = MapWidth * MapTextureSize - left_right_border;

	// Up border collision
	if (y < up_down_border) tempY = up_down_border;

	view.setCenter(tempX, tempY);
}




