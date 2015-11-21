#include "../Headers/frame_rect.h"

using namespace sf;



void FrameRectInit(FrameRects & frame_rect, Type type) {
	std::string entity_type = TypeToString(type);
	frame_rect.move = GetIntRect(entity_type, "MOVE", "animations.txt");
	frame_rect.jump = GetIntRect(entity_type, "JUMP", "animations.txt");
	frame_rect.attack = GetIntRect(entity_type, "ATTACK", "animations.txt");
	frame_rect.stay = GetIntRect(entity_type, "STAY", "animations.txt");
	frame_rect.gravity = GetIntRect(entity_type, "GRAVITY", "animations.txt");
}

void DestroyFrameRects(FrameRects *& frame_rects)
{
	delete frame_rects;
}