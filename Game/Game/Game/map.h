#include <SFML/Graphics.hpp>

const int MapHeight = 25;
const int MapWidth = 100;
const int MapTextureSize = 30;

typedef enum {
	BLOCK,
	FREE_SPACE,
	BORDER
} CellType;

const sf::String TileMap[MapHeight] = {
	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
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
	"b                                  pppppppppppp                                                    b",
	"b                              pppp            pppp                                                b",
	"b                          pppp                    pppp                                            b",
	"b                      pppp                            pppp                                        b",
	"b                  pppp                                    pppp                                    b",
	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"

};
	
struct Cell {
	CellType type;
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

void MapInit(Map & map);

void MapDraw(sf::RenderWindow &window, Map & map);





