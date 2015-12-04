#pragma once
#include <SFML/Graphics.hpp>
#include "consts_and_enums.h"
#include "../Headers/using_json.h"

struct LogicHpBar {
	float health_points;
	float max_health_points;
};

struct VisualHpBar {
	sf::Texture bar_texture;
	sf::Sprite bar_sprite;
	sf::Sprite strip_sprite;
	sf::IntRect strip_rect;
	sf::IntRect bar_rect;
};

struct HpBar {
	LogicHpBar * logic_hp;
	VisualHpBar * visual_hp;
};

HpBar* CreateHpBar(Type type, std::vector<json_spirit::Pair>& int_rects, float curr_hp, float max_hp);

void HpBarInit(HpBar& hp, Type type, std::vector<json_spirit::Pair>& int_rects, float curr_hp, float max_hp);

VisualHpBar* CreateVisualHpBar(Type type, std::vector<json_spirit::Pair>& int_rects);

LogicHpBar* CreateLogicHpBar(float curr_hp, float max_hp);

void LogicHpBarInit(LogicHpBar& hp, float curr_hp, float max_hp);

void VisualHpBarInit(VisualHpBar & hp, Type type, std::vector<json_spirit::Pair>& int_rects);

void HpBarUpdate(HpBar & hp, sf::FloatRect rect_for_place, Type type, float curr_hp);

void HpBarUpdate(HpBar & hp, sf::View & view, float curr_hp);

void DestroyHpBar(HpBar & hp);