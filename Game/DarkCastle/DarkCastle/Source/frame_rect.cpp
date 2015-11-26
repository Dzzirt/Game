#include "../Headers/frame_rect.h"

using namespace sf;


FrameRects* CreateFrameRects(Type type) {
	FrameRects* frame_rects = new FrameRects();
	FrameRectInit(*frame_rects, type);
	return frame_rects;
}

void FrameRectInit(FrameRects & frame_rect, Type type) {
	std::string entity = TypeToString(type);
	frame_rect.move = GetIntRect(entity, "MOVE", "frames.txt");
	frame_rect.jump = GetIntRect(entity, "JUMP", "frames.txt");
	frame_rect.attack = GetIntRect(entity, "ATTACK", "frames.txt");
	frame_rect.stay = GetIntRect(entity, "STAY", "frames.txt");
	frame_rect.gravity = GetIntRect(entity, "GRAVITY", "frames.txt");
}

void DestroyFrameRects(FrameRects *& frame_rects)
{
	delete frame_rects;
}