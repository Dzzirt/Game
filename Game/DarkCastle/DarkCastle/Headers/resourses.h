#pragma once
#include "using_json.h"
#include "level.hpp"


struct Resourses {
	std::vector<json_spirit::Pair>* int_rects;
	std::vector<json_spirit::Pair>* config;
	Level *lvl;
};

Resourses* CreateResourses();

Level* CreateLevel();

void ResInit(Resourses & res);

void LevelInit(Level & level);

void DestroyLevel(Level& level);

void DestroyResourses(Resourses & res);
