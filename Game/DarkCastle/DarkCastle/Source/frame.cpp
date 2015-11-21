#include "../Headers/frame.h"

Frame* CreateFrame(Type type) {
	Frame * frame = new Frame();
	FrameInit(*frame, type);
	return frame;
}

void FrameInit(Frame & frame, Type type) {
	frame.rect = CreateFrameRects(type);
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
	case SWORDSMAN:

		break;
	default:
		break;
	}
}

void DestroyFrame(Frame *& frame)
{
	DestroyFrameRects(frame->rect);
	delete frame;
}