#include "../Headers/bonus_visual.h"

BonusVisual* CreateBonusVisual(BonusType type) {
	BonusVisual* visual = new BonusVisual();
	BonusVisualInit(*visual, type);
	return visual;
}

void BonusVisualInit(BonusVisual& bonus_visual, BonusType type) {
	std::string bon_type = TypeToString(type);
	bonus_visual.image.loadFromFile("Resourses/bonus.png");
	bonus_visual.texture.loadFromImage(bonus_visual.image);
	bonus_visual.sprite.setTexture(bonus_visual.texture);
	bonus_visual.sprite.setTextureRect(GetIntRect("BONUS", bon_type, "frames.txt"));
}

void DestroyBonusVisual(BonusVisual& bonus_visual) {
	delete &bonus_visual;
}