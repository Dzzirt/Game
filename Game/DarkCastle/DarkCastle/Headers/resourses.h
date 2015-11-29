#pragma once
#include "using_json.h"
#include "level.hpp"


struct Resourses {
	std::vector<json_spirit::Pair>* int_rects;
	Level *lvl;
};

Resourses* CreateResourses();

void ResInit(Resourses & res);

Level* CreateLevel();

void LevelInit(Level & level);

void DestroyLevel(Level*& level);
