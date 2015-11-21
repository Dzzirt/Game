#include "../Headers/jump.h"

Jump* CreateJump(Type type) {
	Jump * jump = new Jump();
	JumpingInit(*jump, type);
	return jump;
}

void JumpingInit(Jump & jump, Type type) {
	jump.on_ground = false;
	jump.jump_height_counter = 0.f;
	jump.in_jump = false;
	jump.max_jump = 75.f;
}

void DestroyJump(Jump *& jump)
{
	delete jump;
}
void CheckJumpLogic(Jump& jump, Movement& movement, Animation& animation) {
	if (jump.in_jump && jump.jump_height_counter < jump.max_jump) {
		// Disable attack
		DisableAttack(animation);
		//
		jump.jump_height_counter += movement.step * TimePerFrame.asSeconds();
		movement.delta_y = -movement.step;
		jump.on_ground = false;
		//Jump
	}
	else {
		jump.in_jump = false;
		animation.current_jump_frame = 0.f;
		jump.jump_height_counter = 0;
	}
}

