#include "../Headers/visual.h"
#include "../Headers/level.hpp"
#include "../Headers/safe_delete.h"

Visual* CreateVisual(Type type, sf::FloatRect & rect, std::vector<json_spirit::Pair> & int_rects) {
	Visual * visual = new Visual();
	VisualInit(*visual, type, rect, int_rects);
	return visual;
}
void VisualInit(Visual& visual, Type type, sf::FloatRect & rect, std::vector<json_spirit::Pair> & int_rects) {
	visual.animation = CreateAnimation(type, int_rects);
	visual.rect = new sf::Rect<float>;
	*visual.rect = rect;
}

void DestroyVisual(Visual *& visual){
		DestroyAnimation(visual->animation);
		SafeDelete(visual->rect);
		SafeDelete(visual);
}

