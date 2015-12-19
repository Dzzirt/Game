#pragma once
#include "consts_and_enums.h"
#include "bonus_logic.h"


struct CellLogic {
	int value;
	float duration;
	BonusType type;
	bool is_activated;
};

CellLogic* CreateCellLogic(BonusLogic & b_logic);

void CellLogicInit(CellLogic & cell_logic, BonusLogic & b_logic);

void DestroyCellLogic(CellLogic *& cell_logic);