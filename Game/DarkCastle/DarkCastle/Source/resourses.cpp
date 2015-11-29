#include "../Headers/resourses.h"

Resourses* CreateResourses() {
	Resourses * res = new Resourses();
	ResInit(*res);
	return res;
}

void ResInit(Resourses& res) {
	res.int_rects = GetEntitiesVector("Resourses/frames.txt");
	res.lvl = CreateLevel();
}

Level* CreateLevel() {
	Level* level = new Level();
	LevelInit(*level);
	return level;
}

void LevelInit(Level& level) {
	level.LoadFromFile("Resourses/map.tmx");
}



void DestroyLevel(Level*& level) {
	delete level;
}