#include "SFML/Graphics.hpp"

using namespace sf;

View view;

void getPlayerCoordinateForView(float x, float y)
{
	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

	if (x < 400) tempX = 400;//������� �� ���� ����� �������
	//if (y < 240) tempY = 240;//������� �������
	if (y > MAP_HEIGHT * 30 - 300 ) tempY = MAP_HEIGHT * 30 - 300;//������ �������	
	if (x > MAP_WIDTH * 30 - 400) tempX = MAP_WIDTH * 30 - 400;

	view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������. 
}
