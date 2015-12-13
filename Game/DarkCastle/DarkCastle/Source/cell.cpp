#include "../Headers/cell.h"

Cell* CreateCell(Bonus & bonus) {
	Cell * cell = new Cell();
	CellInit(*cell, bonus);
	return cell;
}

void CellInit(Cell& cell, Bonus & bonus) {
	cell.visual = CreateCellVisual(*bonus.bonus_visual);
	cell.logic = CreateCellLogic(*bonus.bonus_logic);
}

void DestroyCell(Cell& cell) {
	DestroyCellLogic(*cell.logic);
	DestroyCellVisual(*cell.visual);
	delete &cell;
}