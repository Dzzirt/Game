#include "../Headers/consts_and_enums.h"
#include "../Headers/player.h"

void FightLogicInit(FightLogic& fight, Type type) {
	fight.hp_bar = new HpBar();
	HpBarInit(*fight.hp_bar, type);
	fight.attack_occured = false;
	fight.is_dead = false;

	switch (type) {
		case PLAYER:
			fight.health_points = 100.f;
			fight.max_health_points = 100.f;
			fight.damage = CPlayerDamage;
			break;
		case SPEARMAN:
			fight.health_points = 50.f;
			fight.max_health_points = 50.f;
			fight.damage = CEnemyDamage;
			break;
		case SWORDSMAN:
			break;
		default: break;
	}
}

void DestroyFightLogic(FightLogic *& fight)
{
	DestroyHpBar(fight->hp_bar);
	delete fight;
}

void HpBarUpdate(FightLogic & fight, sf::FloatRect rect_for_place, Type type) {
	HpBar& hp = *fight.hp_bar;
	sf::IntRect & hp_strip = hp.strip_rect;
	switch (type) {
	case SPEARMAN:
		hp.bar_sprite.setPosition(rect_for_place.left + (rect_for_place.width / 2.f), rect_for_place.top - 10.f);
		hp.bar_sprite.setOrigin(hp.bar_texture.getSize().x / 2.f, 0);
		break;
	default:
		break;
	}
	float health_in_percent = fight.health_points / fight.max_health_points;
	sf::FloatRect bar_bounds = hp.bar_sprite.getGlobalBounds();
	sf::FloatRect strip_bounds = hp.strip_sprite.getGlobalBounds();
	float border_width = (bar_bounds.width - strip_bounds.width) / 2.f;
	float border_height = (bar_bounds.height - strip_bounds.height) / 2.f;
	hp.strip_sprite.setPosition(bar_bounds.left + border_width, bar_bounds.top + border_height);
	hp.strip_sprite.setTextureRect(sf::IntRect(hp_strip.left, hp_strip.top, hp_strip.width * health_in_percent, hp_strip.height));
}

void PlayerHpBarUpdate(FightLogic & fight, sf::View & view) {
	float x_pos = view.getCenter().x - view.getSize().x / 2.f;
	float y_pos = view.getCenter().y - view.getSize().y / 2.f;
	HpBar& hp = *fight.hp_bar;
	sf::IntRect & hp_strip = hp.strip_rect;
	hp.bar_sprite.setPosition(x_pos, y_pos);
	hp.bar_sprite.setOrigin(0, 0);
	float health_in_percent = fight.health_points / fight.max_health_points;
	sf::FloatRect bar_bounds = hp.bar_sprite.getGlobalBounds();
	sf::FloatRect strip_bounds = hp.strip_sprite.getGlobalBounds();
	float border_left = (bar_bounds.width - strip_bounds.width) / 2.f;
	float border_top = (bar_bounds.height - strip_bounds.height) / 2.f;
	hp.strip_sprite.setPosition(bar_bounds.left + border_left, bar_bounds.top + border_top);
	hp.strip_sprite.setTextureRect(sf::IntRect(0, hp_strip.top, hp_strip.width * health_in_percent, hp_strip.height));
}