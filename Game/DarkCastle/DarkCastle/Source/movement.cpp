#include "../Headers/movement.h"

void MovementInit(Movement & movement, Type type) {
	movement.x_pos = 0;
	movement.y_pos = 0;
	movement.delta_x = 0;
	movement.delta_y = 0;
	movement.state = NONE;
	movement.prev_state = NONE;

	switch (type) {
	case PLAYER:
		movement.step = 150;
		break;
	case SPEARMAN:
		movement.step = 110;
		break;
	case SWORDSMAN:
		break;
	default:
		break;
	}
}

void DestroyMovement(Movement *& movement)
{
	delete movement;
}

void CheckMovementLogic(Movement & movement) {
	switch (movement.state) {
	case LEFT:
		movement.delta_x = -movement.step;
		break;
	case RIGHT:
		movement.delta_x = movement.step;
		break;
	case NONE:
		movement.delta_x = 0;
		break;
	}
}