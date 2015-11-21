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

Frame* CreateFrame(Type type);

void FrameInit(Frame& frame, Type type);

void DestroyFrame(Frame *& frame);
