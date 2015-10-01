#include <SFML/Graphics.hpp>
#include "map.h";
#include "view.h";


using namespace sf;

class Player
{
public:
	Sprite sprite;

	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed;
			dy = 0;
			break;
		case 1: dx = -speed;
			dy = 0;
			break;
		case 2: dx = 0;
			dy = speed;
			break;
		case 3: dx = 0;
			dy = -speed;
			break;
		}
		xPos += dx * time;
		yPos += dy * time;
		speed = 0;
		sprite.setPosition(xPos, yPos);
	}


	void set_speed(float speed)
	{
		this->speed = speed;
	}

	void set_dir(int dir)
	{
		this->dir = dir;
	}


	float x_pos() const
	{
		return xPos;
	}

	float y_pos() const
	{
		return yPos;
	}

	Player(float w, float h, float x, float y, String file)
	{
		this->file = file;
		this->weight = w;
		this->height = h;
		this->xPos = x;
		this->yPos = y;
		image.loadFromFile("images/" + this->file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 60, 90));

		
	}

private:
	float xPos, yPos, weight, height, dx = 0, dy = 0, speed = 0;
	int dir = 0;
	String file;
	Image image;
	Texture texture;

	
};


int main()
{
	RenderWindow window(VideoMode(800, 600), "Lesson 1. kychka-pc.ru");
	Clock clock;
	float currentFrame = 0;
	Player hero(96.0, 96.0, 90, (MAP_HEIGHT - 1) * 30 - 90, "hero.png");
	view.reset(FloatRect(0, 0, 800, 600));

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			hero.set_dir(1);
			hero.set_speed(0.14);
			currentFrame += time * 0.005;
			if (currentFrame > 3)
			{
				currentFrame -= 3;
			}
			//hero.sprite.setTextureRect(IntRect(96 * int(currentFrame), 96, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			hero.set_dir(0);
			hero.set_speed(0.14);
			currentFrame += time * 0.005;
			if (currentFrame > 3)
			{
				currentFrame -= 3;
			}
			//hero.sprite.setTextureRect(IntRect(96 * int(currentFrame), 192, 96, 96));
		}
		getPlayerCoordinateForView(hero.x_pos() + 30, hero.y_pos() + 45);
		hero.update(time);
		window.setView(view);
		window.clear();
		for (int i = 0; i < MAP_HEIGHT; i++)
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 30, 30));
				if (TileMap[i][j] == 'b') s_map.setTextureRect(IntRect(31, 0, 30, 30));
				if ((TileMap[i][j] == 'p')) s_map.setTextureRect(IntRect(62, 0, 30, 30));


				s_map.setPosition(j * 30, i * 30);

				window.draw(s_map);
			}
		window.draw(hero.sprite);
		window.display();
	}

	return 0;
}
