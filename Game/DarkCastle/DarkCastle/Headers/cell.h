#pragma once
#include "cell_logic.h"
#include "cell_visual.h"
#include "bonus.h"


struct Cell {
	CellVisual * visual;
	CellLogic * logic;
};

Cell* CreateCell(Bonus & bonus);

void CellInit(Cell & cell, Bonus & bonus);

void DestroyCell(Cell & cell);