#include "../Headers/logic_AI.h"
#include "../Headers/consts_and_enums.h"
#include "../Headers/safe_delete.h"

LogicAI* CreateAI(Type type) {
	LogicAI* ai = new LogicAI();
	InitLogicAI(*ai, type);
	return ai;
}

void InitLogicAI(LogicAI & ai, Type type) {
	ai.current_distance = 0.f;
	ai.stay_time = 0.f;
	ai.state = NOT_DETECT;
	ai.field_of_view = 30.f;
	switch (type) {
	case SPEARMAN:
		ai.max_distance = float(GetRandomInt(20, 50));
		ai.max_stay_time = GetRandomFloat(1, 5, 1);
	case JELLY_BOSS:
		ai.max_distance = float(GetRandomInt(20, 70));
		ai.max_stay_time = GetRandomFloat(1, 10, 1);
	case JELLY:
		ai.max_distance = float(GetRandomInt(50, 100));
		ai.max_stay_time = GetRandomFloat(1, 7, 1);
	default:
		break;
	}

}

void DestroyAI(LogicAI *& ai) {
	SafeDelete(ai);
}