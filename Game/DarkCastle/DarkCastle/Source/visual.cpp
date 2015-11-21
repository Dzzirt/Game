#include "../Headers/visual.h"
#include "../Headers/level.hpp"

void VisualInit(Visual& visual, Type type, sf::FloatRect & rect) {
	visual.animation = new Animation();
	visual.rect = new sf::Rect<float>();
	*visual.rect = rect;
	AnimationInit(*visual.animation, type);
}

void DestroyVisual(Visual*& visual){
	DestroyAnimation(visual->animation);
	delete visual->rect;
	delete visual;
}

