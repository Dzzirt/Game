#include "../Headers/visual.h"

void VisualInit(Visual& visual, Type type, sf::FloatRect & rect) {
	visual.animation = new Animation();
	visual.rect = new sf::Rect<float>();
	*visual.rect = rect;
	AnimationInit(*visual.animation, type);
}

