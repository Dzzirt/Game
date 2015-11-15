#pragma once
#include "frame_rect.h"


struct Frame {
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	float displacement;
	FrameRects* rect;
};

void FrameInit(Frame& frame, Type type);
