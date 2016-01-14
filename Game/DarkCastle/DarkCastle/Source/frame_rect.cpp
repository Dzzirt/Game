#include "../Headers/frame_rect.h"
#include "../Headers/safe_delete.h"

using namespace sf;


FrameRects* CreateFrameRects(Type type, std::vector<json_spirit::Pair> & int_rects) {
	FrameRects* frame_rects = new FrameRects();
	FrameRectInit(*frame_rects, type, int_rects);
	return frame_rects;
}

void FrameRectInit(FrameRects & frame_rect, Type type, std::vector<json_spirit::Pair> & int_rects) {
	std::string entity = TypeToString(type);
	frame_rect.move = GetIntRect(int_rects, entity, "MOVE");
	frame_rect.jump = GetIntRect(int_rects, entity, "JUMP");
	if (type == JELLY_BOSS)
	{
		frame_rect.attack_rects.push_back(GetIntRect(int_rects, entity, "ATTACK0"));
		frame_rect.attack_rects.push_back(GetIntRect(int_rects, entity, "ATTACK1"));
		frame_rect.attack_rects.push_back(GetIntRect(int_rects, entity, "ATTACK2"));
	}
	else
	{
		frame_rect.attack_rects.push_back(GetIntRect(int_rects, entity, "ATTACK"));
	}
	frame_rect.stay = GetIntRect(int_rects, entity, "STAY");
	frame_rect.gravity = GetIntRect(int_rects, entity, "GRAVITY");
}

void DestroyFrameRects(FrameRects *& frame_rects)
{
	SafeDelete(frame_rects);
}