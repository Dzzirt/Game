#pragma once
#include "consts_and_enums.h"
#include "movement.h"
#include "animation.h"

struct Jump {
	bool in_jump;
	float max_jump;
	bool on_ground;
	float jump_height_counter;
};

Jump* CreateJump(Type type);

void JumpingInit(Jump & jump, Type type);

void CheckJumpLogic(Jump & jump, Movement & movement, Animation & animation);

void DestroyJump(Jump *& jump);

