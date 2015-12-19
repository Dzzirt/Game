#include "../Headers/hp_bar.h"
#include "../Headers/safe_delete.h"

HpBar* CreateHpBar(Type type, std::vector<json_spirit::Pair>& int_rects, float curr_hp, float max_hp) {
	HpBar * hp = new HpBar();
	HpBarInit(*hp, type, int_rects, curr_hp, max_hp);
	return hp;
}

void HpBarInit(HpBar& hp, Type type, std::vector<json_spirit::Pair>& int_rects,  float curr_hp, float max_hp) {
	hp.logic_hp = CreateLogicHpBar(curr_hp, max_hp);
	hp.visual_hp = CreateVisualHpBar(type, int_rects);
}

VisualHpBar* CreateVisualHpBar(Type type, std::vector<json_spirit::Pair> & int_rects) {
	VisualHpBar* visual_hp = new VisualHpBar();
	VisualHpBarInit(*visual_hp, type, int_rects);
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

void VisualHpBarInit(VisualHpBar & hp, Type type, std::vector<json_spirit::Pair>& int_rects) {
	switch (type) {
	case PLAYER:
		hp.bar_texture.loadFromFile("Resourses/Hero/hero_hp.png");
		hp.bar_rect = GetIntRect(int_rects, "PLAYER_HP", "HP_BAR");
		hp.strip_rect = GetIntRect(int_rects, "PLAYER_HP", "HP_STRIP");
		hp.strip_sprite.setRotation(-90);
		hp.bar_sprite.setRotation(-90);
		break;
	default:
		hp.bar_texture.loadFromFile("Resourses/Enemy/enemy_hp.png");
		hp.bar_rect = GetIntRect(int_rects, "BASIC_ENEMY_HP", "HP_BAR");
		hp.strip_rect = GetIntRect(int_rects, "BASIC_ENEMY_HP", "HP_STRIP");	
		break;
	}
	hp.bar_sprite.setTexture(hp.bar_texture);
	hp.strip_sprite.setTexture(hp.bar_texture);
	hp.bar_sprite.setTextureRect(sf::IntRect(hp.bar_rect.left, hp.bar_rect.top, hp.bar_rect.width, hp.bar_rect.height));
	hp.strip_sprite.setTextureRect(sf::IntRect(hp.strip_rect.left, hp.strip_rect.top, hp.strip_rect.width, hp.strip_rect.height));

}

void HpBarUpdate(HpBar & hp, sf::FloatRect rect_for_place, Type type, float curr_hp) {
	VisualHpBar & visual_hp = *hp.visual_hp;
	LogicHpBar & logic_hp = *hp.logic_hp;
	logic_hp.health_points = curr_hp;
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
	float max_strip_width = float(visual_hp.strip_rect.width);
	float border_width = (bar_bounds.width - max_strip_width) / 2.f;
	float border_height = (bar_bounds.height - strip_bounds.height) / 2.f;
	visual_hp.strip_sprite.setPosition(bar_bounds.left + border_width, bar_bounds.top + border_height);
	visual_hp.strip_sprite.setTextureRect(sf::IntRect(hp_strip.left, hp_strip.top, int(hp_strip.width * health_in_percent), hp_strip.height));
}

void HpBarUpdate(HpBar & hp, sf::View & view, float curr_hp) {
	VisualHpBar & visual_hp = *hp.visual_hp;
	LogicHpBar & logic_hp = *hp.logic_hp;
	logic_hp.health_points = curr_hp;
	float x_pos = view.getCenter().x - view.getSize().x / 2.f + 10;
	float y_pos = view.getCenter().y - view.getSize().y / 2.f + 400 + visual_hp.bar_rect.width;
	sf::IntRect & hp_strip = visual_hp.strip_rect;
	visual_hp.bar_sprite.setPosition(x_pos, y_pos);
	visual_hp.bar_sprite.setOrigin(0, 0);
	float health_in_percent = logic_hp.health_points / logic_hp.max_health_points;
	sf::FloatRect bar_bounds = visual_hp.bar_sprite.getGlobalBounds();
	sf::FloatRect strip_bounds = visual_hp.strip_sprite.getGlobalBounds();
	float border_top = (bar_bounds.height - visual_hp.strip_rect.width) / 2.f;
	float border_left = (bar_bounds.width - strip_bounds.width) / 2.f;
	visual_hp.strip_sprite.setPosition(bar_bounds.left + border_left, bar_bounds.top + bar_bounds.height - border_top);
	visual_hp.strip_sprite.setTextureRect(sf::IntRect(0, hp_strip.top, int(hp_strip.width * health_in_percent), hp_strip.height));
}

void DestroyVisualHpBar(VisualHpBar *& visual){
	SafeDelete(visual);
}

void DestroyLogicHpBar(LogicHpBar *& logic)
{
	SafeDelete(logic);
}

void DestroyHpBar(HpBar *& hp)
{
	DestroyVisualHpBar(hp->visual_hp);
	DestroyLogicHpBar(hp->logic_hp);
	SafeDelete(hp);
}
