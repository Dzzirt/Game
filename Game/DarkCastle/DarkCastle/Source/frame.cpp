#include "../Headers/frame.h"
#include "../Headers/safe_delete.h"

Frame* CreateFrame(Type type, std::vector<json_spirit::Pair> & int_rects) {
	Frame * frame = new Frame();
	FrameInit(*frame, type, int_rects);
	return frame;
}

void FrameInit(Frame & frame, Type type, std::vector<json_spirit::Pair> & int_rects) {
	frame.rect = CreateFrameRects(type, int_rects);
	frame.displacement = 0.f;
	switch (type) {
	case PLAYER:
		frame.image.loadFromFile("Resourses/Hero/hero.png");
		frame.texture.loadFromImage(frame.image);
		frame.sprite.setTexture(frame.texture);
		break;
	case SPEARMAN:
		frame.image.loadFromFile("Resourses/Enemy/spearman.png");
		frame.texture.loadFromImage(frame.image);
		frame.sprite.setTexture(frame.texture);
		break;
	case JELLY_BOSS:
		frame.image.loadFromFile("Resourses/Enemy/jelly_boss.png");
		frame.texture.loadFromImage(frame.image);
		frame.sprite.setTexture(frame.texture);
		break;
	case JELLY:
		frame.image.loadFromFile("Resourses/Enemy/jelly.png");
		frame.texture.loadFromImage(frame.image);
		frame.sprite.setTexture(frame.texture);
		break;
	default:
		break;
	}
}

void DestroyFrame(Frame *& frame)
{
	DestroyFrameRects(frame->rect);
	SafeDelete(frame);
}