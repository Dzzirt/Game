#pragma once
#include "consts_and_enums.h"


struct Movement {
	float x_pos;
	float y_pos;
	float default_step;
	float step;
	float delta_x;
	float delta_y;
	State state;
	State prev_state;
};

Movement* CreateMovement(Type type);

void MovementInit(Movement & movement, Type type);

void CheckMovementLogic(Movement & movement);

void DestroyMovement(Movement & movement);