
#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Libs/TinyXML/tinyxml.h"

struct Object
{
    int GetPropertyInt(std::string name);
    float GetPropertyFloat(std::string name);
    std::string GetPropertyString(std::string name);

    std::string name;
    std::string type;
    sf::Rect<float> rect;
    std::map<std::string, std::string> properties;

	sf::Sprite sprite;
};

struct Layer
{
    int opacity;
    std::vector<sf::Sprite> tiles;
};

class Level
{
public:
	int width;
	int height;
	int tileWidth;
	int tileHeight;

	bool LoadFromFile(std::string filename);
	std::vector<Object> Level::GetMatchObjects(int from, int to, std::string name);
    Object GetObject(std::string name);
    std::vector<Object> GetObjects(std::string name);
	std::vector<Object> GetAllObjects()const;
    void Draw(sf::RenderWindow &window);
	sf::Vector2i GetTileSize();

private:
		std::vector<Object> objects;
    int firstTileID;
    sf::Rect<float> drawingBounds;
    sf::Texture tilesetImage;

    std::vector<Layer> layers;
};

///////////////////////////////////////




#endif
