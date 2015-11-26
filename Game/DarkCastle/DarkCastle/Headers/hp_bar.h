#pragma once
#include <SFML/Graphics.hpp>
#include "consts_and_enums.h"

struct LogicHpBar {
	float health_points;
	float max_health_points;
	int max_strip_width;
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

HpBar* CreateHpBar(Type type, float curr_hp, float max_hp);

void HpBarInit(HpBar& hp, Type type, float curr_hp, float max_hp);

VisualHpBar* CreateVisualHpBar(Type type);

LogicHpBar* CreateLogicHpBar(float curr_hp, float max_hp, Type type);

void LogicHpBarInit(LogicHpBar& hp, float curr_hp, float max_hp, Type type);

void VisualHpBarInit(VisualHpBar & hp, Type type);

void HpBarUpdate(HpBar & hp, sf::FloatRect rect_for_place, Type type, float curr_hp);

void HpBarUpdate(HpBar & hp, sf::View & view, float curr_hp);

void DestroyHpBar(HpBar *& hp);