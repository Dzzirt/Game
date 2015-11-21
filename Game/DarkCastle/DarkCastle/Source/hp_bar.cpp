#include "../Headers/hp_bar.h"
#include "../Headers/using_json.h"

HpBar* CreateHpBar(Type type) {
	HpBar * hp = new HpBar();
	HpBarInit(*hp, type);
	return hp;
}
void HpBarInit(HpBar & hp, Type type) {
	switch (type) {
	case PLAYER:
		hp.bar_texture.loadFromFile("Resourses/Hero/hero_hp.png");
		hp.bar_rect = GetIntRect("PLAYER", "HP_BAR", "bars.txt");
		hp.strip_rect = GetIntRect("PLAYER", "HP_STRIP", "bars.txt");
		break;
	default:
		hp.bar_texture.loadFromFile("Resourses/Enemy/enemy_hp.png");
		hp.bar_rect = GetIntRect("BASIC_ENEMY", "HP_BAR", "bars.txt");
		hp.strip_rect = GetIntRect("BASIC_ENEMY", "HP_STRIP", "bars.txt");	
		break;
	}
	hp.bar_sprite.setTexture(hp.bar_texture);
	hp.strip_sprite.setTexture(hp.bar_texture);
	hp.bar_sprite.setTextureRect(sf::IntRect(hp.bar_rect.left, hp.bar_rect.top, hp.bar_rect.width, hp.bar_rect.height));
	hp.strip_sprite.setTextureRect(sf::IntRect(hp.strip_rect.left, hp.strip_rect.top, hp.strip_rect.width, hp.strip_rect.height));

}

void DestroyHpBar(HpBar *& hp)
{
	delete hp;
}
