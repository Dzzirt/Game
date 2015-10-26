#pragma once
#include <SFML/Graphics.hpp>

const float EnemyHpBarWidth = 30.f;
const float EnemyHpBarHeight = 3.f;
const float EnemyHpStripWidth = 28.f;
const float PlayerHpBarHeight = 28.f;
const float PlayerHpBarWidth = 244.f;
const float PlayerHpStripWidth = 184.f;
const float PlayerHpStripHeight = 14.f;

struct HpBar {
	sf::Texture bar_texture;
	sf::Sprite bar_sprite;
	sf::Sprite strip_sprite;

};