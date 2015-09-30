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
		switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
		case 0: dx = speed;
			dy = 0;
			break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
		case 1: dx = -speed;
			dy = 0;
			break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
		case 2: dx = 0;
			dy = speed;
			break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
		case 3: dx = 0;
			dy = -speed;
			break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
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
		image.createMaskFromColor(Color(41, 33, 59));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, weight, height));

		
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
	RenderWindow window(VideoMode(1024, 768), "Lesson 1. kychka-pc.ru");
	Clock clock;
	float currentFrame = 0;
	Player hero(96.0, 96.0, 250, 250, "hero.png");
	view.reset(FloatRect(0, 0, 640, 480));

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

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			hero.set_dir(3);
			hero.set_speed(0.1);
			currentFrame += 0.005 * time;
			if (currentFrame > 3)
			{
				currentFrame -= 3;
			}
			hero.sprite.setTextureRect(IntRect(96 * int(currentFrame), 288, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			hero.set_dir(2);
			hero.set_speed(0.1);
			currentFrame += time * 0.005;
			if (currentFrame > 3)
			{
				currentFrame -= 3;
			}
			hero.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			hero.set_dir(1);
			hero.set_speed(0.1);
			currentFrame += time * 0.005;
			if (currentFrame > 3)
			{
				currentFrame -= 3;
			}
			hero.sprite.setTextureRect(IntRect(96 * int(currentFrame), 96, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			hero.set_dir(0);
			hero.set_speed(0.1);
			currentFrame += time * 0.005;
			if (currentFrame > 3)
			{
				currentFrame -= 3;
			}
			hero.sprite.setTextureRect(IntRect(96 * int(currentFrame), 192, 96, 96));
		}
		getPlayerCoordinateForView(hero.x_pos(), hero.y_pos());
		hero.update(time);
		window.setView(view);
		window.clear();
		for (int i = 0; i < MAP_HEIGHT; i++)
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 's') s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));


				s_map.setPosition(j * 32, i * 32);

				window.draw(s_map);
			}
		window.draw(hero.sprite);
		window.display();
	}

	return 0;
}
