#include "../Headers/bonus_visual.h"

BonusVisual* CreateBonusVisual(BonusType type, std::vector<json_spirit::Pair> & int_rects) {
	BonusVisual* visual = new BonusVisual();
	BonusVisualInit(*visual, type, int_rects);
	return visual;
}

void BonusVisualInit(BonusVisual& bonus_visual, BonusType type, std::vector<json_spirit::Pair> & int_rects) {
	std::string bon_type = TypeToString(type);
	bonus_visual.image.loadFromFile("Resourses/bonus.png");
	bonus_visual.texture.loadFromImage(bonus_visual.image);
	bonus_visual.sprite.setTexture(bonus_visual.texture);
	bonus_visual.sprite.setTextureRect(GetIntRect(int_rects, "BONUS", bon_type));
}

void DestroyBonusVisual(BonusVisual& bonus_visual) {
	delete &bonus_visual;
}