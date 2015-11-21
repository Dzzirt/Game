#include "../Headers/visual.h"
#include "../Headers/level.hpp"

Visual* CreateVisual(Type type, sf::FloatRect & rect) {
	Visual * visual = new Visual();
	VisualInit(*visual, type, rect);
	return visual;
}
void VisualInit(Visual& visual, Type type, sf::FloatRect & rect) {
	visual.animation = CreateAnimation(type);
	visual.rect = new sf::Rect<float>;
	*visual.rect = rect;
}

void DestroyVisual(Visual*& visual){
	DestroyAnimation(visual->animation);
	delete visual->rect;
	delete visual;
}

