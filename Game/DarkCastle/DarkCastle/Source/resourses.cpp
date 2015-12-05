#include "../Headers/resourses.h"

Resourses* CreateResourses() {
	Resourses * res = new Resourses();
	ResInit(*res);
	return res;
}

Level* CreateLevel() {
	Level* level = new Level();
	LevelInit(*level);
	return level;
}

void ResInit(Resourses& res) {
	res.int_rects = GetEntitiesVector("Resourses/frames.txt");
	res.config = GetEntitiesVector("Resourses/bonus_config.txt");
	res.lvl = CreateLevel();
}

void LevelInit(Level& level) {
	level.LoadFromFile("Resourses/map.tmx");
}


void DestroyResourses(Resourses & res) {
	delete & res;
}

void DestroyLevel(Level& level) {
	delete &level;
}