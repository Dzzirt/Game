#include "../Headers/logic.h"

void LogicInit (Logic & logic, Type type){
	logic.fight = new FightLogic();
	logic.movement = new Movement();
	FightLogicInit(*logic.fight, type);
	MovementInit(*logic.movement, type);
}