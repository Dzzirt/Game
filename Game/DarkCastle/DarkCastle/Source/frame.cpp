#include "../Headers/frame.h"


void FrameInit(Frame & frame, Type type) {
	frame.displacement = 0.f;
	frame.rect = new FrameRects();
	FrameRectInit(*frame.rect, type);
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