#include "../Headers/cell_logic.h"

CellLogic* CreateCellLogic(BonusLogic & b_logic) {
	CellLogic * cell_logic = new CellLogic();
	CellLogicInit(*cell_logic, b_logic);
	return cell_logic;
}

void CellLogicInit(CellLogic & cell_logic, BonusLogic & b_logic) {
	cell_logic.type = b_logic.bonus_type;
	cell_logic.value = b_logic.value;
	cell_logic.duration = b_logic.duration;
	cell_logic.is_activated = false;
}

void DestroyCellLogic(CellLogic& cell_logic) {
	delete &cell_logic;
}