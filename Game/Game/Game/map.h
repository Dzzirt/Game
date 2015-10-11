#include <SFML/Graphics.hpp>

const int MapHeight = 25;
const int MapWidth = 100;
const int MapTextureSize = 30;
const float GroundY = (MapHeight - 1) * MapTextureSize - 90;
const float FallingSpeedCoef = 1.6f;
const float JumpingSpeedCoef = 1.3f;

typedef enum {
	BLOCK,
	FREE_SPACE,
	BORDER
} CellType;

const sf::String TileMap[MapHeight] = {
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"b                                                                                                  b",
	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"

};
	
struct Cell {
	CellType type;
	bool with_player = false;
	sf::Sprite sprite;
};

struct Map {
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	unsigned width;
	unsigned height;
	Cell * cells;
};

void MapInit(Map *& map);

void MapDraw(sf::RenderWindow &window, Map & map);





