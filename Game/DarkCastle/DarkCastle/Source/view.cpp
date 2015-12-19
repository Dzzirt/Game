#include "../Headers/view.h"
#include "../Headers/safe_delete.h"

sf::View* CreateView() {
	sf::View * view = new sf::View();
	view->reset(sf::FloatRect(0.f, 0.f, float(WindowWidth), float(WindowHeight)));
	return view;
}

void ViewUpdate(sf::View& view, const Movement& movement, const Level& level, float displacement) {
	float left_right_border = view.getSize().x / 2;
	float up_down_border = view.getSize().y / 2;
	int map_height = level.height * level.tileHeight;
	int map_width = level.width * level.tileWidth;

	float x_pos = movement.x_pos - displacement;
	float y_pos = movement.y_pos;
	float tempX = x_pos;
	float tempY = y_pos;

	if (x_pos < left_right_border) {
		tempX = left_right_border;
	}
	if (y_pos > map_height - up_down_border) {
		tempY = map_height - up_down_border;
	}
	if (x_pos > map_width - left_right_border) {
		tempX = map_width - left_right_border;
	}
	if (y_pos < up_down_border) {
		tempY = up_down_border;
	}

	view.setCenter(tempX, tempY);
}

void DestroyView(sf::View *& view) {
	SafeDelete(view);
}