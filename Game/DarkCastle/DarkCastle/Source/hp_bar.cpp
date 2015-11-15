#include "../Headers/hp_bar.h"
#include "../Headers/using_json.h"


void HpBarInit(HpBar & hp, Type type) {
	sf::IntRect hp_rect;
	switch (type) {
	case PLAYER:
		hp.bar_texture.loadFromFile("Resourses/Hero/hero_hp.png");
		hp_rect = GetIntRect("PLAYER", "HP_BAR", "bars.txt");
		hp.strip_rect = GetIntRect("PLAYER", "HP_STRIP", "bars.txt");
		break;
	default:
		hp.bar_texture.loadFromFile("Resourses/Enemy/enemy_hp.png");
		hp_rect = GetIntRect("ENEMY", "HP_BAR", "bars.txt");
		hp.strip_rect = GetIntRect("ENEMY", "HP_STRIP", "bars.txt");	
		break;
	}
	hp.bar_sprite.setTexture(hp.bar_texture);
	hp.strip_sprite.setTexture(hp.bar_texture);
	hp.bar_sprite.setTextureRect(sf::IntRect(hp_rect.left, hp_rect.top, hp_rect.width, hp_rect.height));
	hp.strip_sprite.setTextureRect(sf::IntRect(hp.strip_rect.left, hp.strip_rect.top, hp.strip_rect.width, hp.strip_rect.height));

}

