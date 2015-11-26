#include "../Headers/logic_AI.h"
#include "../Headers/consts_and_enums.h"

LogicAI* CreateAI(Type type) {
	LogicAI* ai = new LogicAI();
	InitLogicAI(*ai, type);
	return ai;
}

void InitLogicAI(LogicAI & ai, Type type) {
	ai.current_distance = 0.f;
	ai.stay_time = 0.f;
	ai.state = NOT_DETECT;
	ai.field_of_view = 20.f;
	switch (type) {
	case SPEARMAN:
		ai.max_distance = 50.f;
		ai.max_stay_time = 3.f;
	default:
		break;
	}

}