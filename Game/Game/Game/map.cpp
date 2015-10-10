#include "map.h"

using namespace sf;

void MapInit(Map& map) {
	char border = 'b';
	char platform = 'p';
	char space = ' ';
	map.image.loadFromFile("images/map.png");
	map.texture.loadFromImage(map.image);
	map.width = MapWidth;
	map.height = MapHeight;
	
	// Смысл в том что создаем массив указателе	й Cell для того чтобы в завис от того что в карте, рисовать и перемещать эти ячейки

	Cell* & cells = map.cells;
	cells = new Cell[map.height * map.width];
	for (size_t i = 0; i < map.height; i++) {
		for (size_t j = 0; j < map.width; j++) {
			const size_t index = i * map.width + j;
			Sprite& sprite = cells[index].sprite;
			sprite.setPosition(MapTextureSize * j, MapTextureSize * i);
			sprite.setTexture(map.texture);
			if (TileMap[i][j] == platform) {
				cells[index].type = BLOCK;
				sprite.setTextureRect(IntRect(62, 0, MapTextureSize, MapTextureSize));
			}
			else if (TileMap[i][j] == space) {
				cells[index].type = FREE_SPACE;
				sprite.setTextureRect(IntRect(0, 0, MapTextureSize, MapTextureSize));
			}
			else if (TileMap[i][j] == border) {
				cells[index].type = BORDER;
				sprite.setTextureRect(IntRect(32, 0, MapTextureSize, MapTextureSize));
			}
		}
	}
}

void MapDraw(sf::RenderWindow& window, Map& map) {
	Cell* cells = map.cells;
	for (size_t i = 0; i < map.width * map.height; i++) {
		window.draw(cells[i].sprite);
	}
}
