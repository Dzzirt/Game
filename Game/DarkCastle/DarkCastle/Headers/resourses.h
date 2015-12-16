#pragma once
#include "using_json.h"
#include "level.hpp"


struct Resourses {
	std::vector<json_spirit::Pair>* int_rects;
	std::vector<json_spirit::Pair>* config;
	Level *lvl;
	int curr_lvl_num;
};

Resourses* CreateResourses();

Level* CreateLevel(std::string map_name);

void ResInit(Resourses & res);

void LevelInit(Level & level, std::string map_name);

void DestroyLevel(Level& level);

void DestroyResourses(Resourses & res);
