#include "../Headers/movement.h"

Movement* CreateMovement(Type type) {
	Movement* movement = new Movement();
	MovementInit(*movement, type);
	return movement;
}
void MovementInit(Movement & movement, Type type) {
	movement.x_pos = 0;
	movement.y_pos = 0;
	movement.delta_x = 0;
	movement.delta_y = 0;
	movement.state = NONE;
	movement.prev_state = NONE;

	switch (type) {
	case PLAYER:
		movement.state = NONE;
		movement.step = 150;
		break;
	case SPEARMAN:
		movement.state = LEFT;
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