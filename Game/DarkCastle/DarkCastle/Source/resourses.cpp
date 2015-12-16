#include "../Headers/resourses.h"

Resourses* CreateResourses() {
	Resourses * res = new Resourses();
	ResInit(*res);
	return res;
}

Level* CreateLevel(std::string map_name)
{
	Level* level = new Level();
	LevelInit(*level, map_name);
	return level;
}

void ResInit(Resourses& res) {
	res.int_rects = GetEntitiesVector("Resourses/frames.txt");
	res.config = GetEntitiesVector("Resourses/bonus_config.txt");
	res.lvl = CreateLevel("map.tmx");
	res.curr_lvl_num = 0;
}

void LevelInit(Level & level, std::string map_name)
{
	level.LoadFromFile("Resourses/" + map_name);
}


void DestroyResourses(Resourses & res) {
	delete & res;
}

void DestroyLevel(Level& level) {
	delete &level;
}