#include "../Headers/resourses.h"
#include "../Headers/safe_delete.h"

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
	res.int_rects = GetEntitiesVector("Resourses/JSON/frames.txt");
	res.config = GetEntitiesVector("Resourses/JSON/bonus_config.txt");
	res.lvl = CreateLevel("Resourses/Maps/map.tmx");
	res.curr_lvl_num = 0;
}

void LevelInit(Level & level, std::string map_name)
{
	level.LoadFromFile(map_name);
}

void DestroyEntitiesVector(std::vector<json_spirit::Pair> *& entities){
	SafeDelete(entities);
}

void DestroyResourses(Resourses *& res) {
	DestroyEntitiesVector(res->config);
	DestroyEntitiesVector(res->int_rects);
	DestroyLevel(res->lvl);
	SafeDelete(res);
}

void DestroyLevel(Level*& level) {
	SafeDelete(level);
}