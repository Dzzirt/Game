#include "../Headers/hp_bar.h"
#include "../Headers/using_json.h"

HpBar* CreateHpBar(Type type, float curr_hp, float max_hp) {
	HpBar * hp = new HpBar();
	HpBarInit(*hp, type, curr_hp, max_hp);
	return hp;
}

void HpBarInit(HpBar& hp, Type type, float curr_hp, float max_hp) {
	hp.logic_hp = CreateLogicHpBar(curr_hp, max_hp);
	hp.visual_hp = CreateVisualHpBar(type);
}

VisualHpBar* CreateVisualHpBar(Type type) {
	VisualHpBar* visual_hp = new VisualHpBar();
	VisualHpBarInit(*visual_hp, type);
	return visual_hp;
}

LogicHpBar* CreateLogicHpBar(float curr_hp, float max_hp) {
	LogicHpBar* logic_hp = new LogicHpBar();
	LogicHpBarInit(*logic_hp, curr_hp, max_hp);
	return logic_hp;
}

void LogicHpBarInit(LogicHpBar& hp, float curr_hp, float max_hp) {
	hp.health_points = curr_hp;
	hp.max_health_points = max_hp;
}

void VisualHpBarInit(VisualHpBar & hp, Type type) {
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

void HpBarUpdate(HpBar & hp, sf::FloatRect rect_for_place, Type type) {
	VisualHpBar & visual_hp = *hp.visual_hp;
	LogicHpBar & logic_hp = *hp.logic_hp;
	sf::IntRect & hp_strip = visual_hp.strip_rect;
	switch (type) {
	case SPEARMAN:
		visual_hp.bar_sprite.setPosition(rect_for_place.left + (rect_for_place.width / 2.f), rect_for_place.top - 10.f);
		visual_hp.bar_sprite.setOrigin(visual_hp.bar_texture.getSize().x / 2.f, 0);
		break;
	default:
		break;
	}
	float health_in_percent = logic_hp.health_points / logic_hp.max_health_points;
	sf::FloatRect bar_bounds = visual_hp.bar_sprite.getGlobalBounds();
	sf::FloatRect strip_bounds = visual_hp.strip_sprite.getGlobalBounds();
	float border_width = (bar_bounds.width - strip_bounds.width) / 2.f;
	float border_height = (bar_bounds.height - strip_bounds.height) / 2.f;
	visual_hp.strip_sprite.setPosition(bar_bounds.left + border_width, bar_bounds.top + border_height);
	visual_hp.strip_sprite.setTextureRect(sf::IntRect(hp_strip.left, hp_strip.top, int(hp_strip.width * health_in_percent), hp_strip.height));
}

void HpBarUpdate(HpBar & hp, sf::View & view) {
	VisualHpBar & visual_hp = *hp.visual_hp;
	LogicHpBar & logic_hp = *hp.logic_hp;
	float x_pos = view.getCenter().x - view.getSize().x / 2.f;
	float y_pos = view.getCenter().y - view.getSize().y / 2.f;
	sf::IntRect & hp_strip = visual_hp.strip_rect;
	visual_hp.bar_sprite.setPosition(x_pos, y_pos);
	visual_hp.bar_sprite.setOrigin(0, 0);
	float health_in_percent = logic_hp.health_points / logic_hp.max_health_points;
	sf::FloatRect bar_bounds = visual_hp.bar_sprite.getGlobalBounds();
	sf::FloatRect strip_bounds = visual_hp.strip_sprite.getGlobalBounds();
	float border_left = (bar_bounds.width - strip_bounds.width) / 2.f;
	float border_top = (bar_bounds.height - strip_bounds.height) / 2.f;
	visual_hp.strip_sprite.setPosition(bar_bounds.left + border_left, bar_bounds.top + border_top);
	visual_hp.strip_sprite.setTextureRect(sf::IntRect(0, hp_strip.top, int(hp_strip.width * health_in_percent), hp_strip.height));
}

void DestroyHpBar(HpBar *& hp)
{
	delete hp;
}
