#pragma once
#include "../Headers/consts_and_enums.h"

enum EntityState {
	NOT_DETECT,
	DETECT
};

struct LogicAI {
	float max_distance;
	float current_distance;
	float stay_time;
	float max_stay_time;
	float field_of_view;
	EntityState state;
};

LogicAI* CreateAI(Type type);

void InitLogicAI(LogicAI & ai, Type type);