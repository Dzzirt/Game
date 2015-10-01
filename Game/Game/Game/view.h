#include "SFML/Graphics.hpp"

using namespace sf;

View view;

void getPlayerCoordinateForView(float x, float y)
{
	float tempX = x; float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края

	if (x < 400) tempX = 400;//убираем из вида левую сторону
	//if (y < 240) tempY = 240;//верхнюю сторону
	if (y > MAP_HEIGHT * 30 - 300 ) tempY = MAP_HEIGHT * 30 - 300;//нижнюю сторону	
	if (x > MAP_WIDTH * 30 - 400) tempX = MAP_WIDTH * 30 - 400;

	view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты. 
}
