#include "map.h"
#include "player.h"

using namespace sf;


void GetPlayerCoordinateForView(sf::View& view, float x, float y) {
	float left_right_border = view.getSize().x / 2;
	float up_down_border = view.getSize().y / 2;
	float tempX = x;
	float tempY = y;

	// Left border collision
	if (x < left_right_border) tempX = left_right_border;

	// Down border collision
	if (y > MapHeight * MapTextureSize - up_down_border) tempY = MapHeight * MapTextureSize - up_down_border;

	// Right border collision
	if (x > MapWidth * MapTextureSize - left_right_border) tempX = MapWidth * MapTextureSize - left_right_border;

	// Up border collision
	if (y < up_down_border) tempY = up_down_border;

	view.setCenter(tempX, tempY);
}

void GravityAnimation(Player& player) {
	if (!player.on_ground && !player.in_jump) {
		// Disable attack
		player.left_attack = false;
		player.right_attack = false;
		//
		player.sprite.setTextureRect(IntRect(117, 87, 39, 45));
	}
}

void JumpAnimation(Player& player, float game_step) {
	if (player.in_jump) {
		player.current_jump_frame += float(0.07 * game_step);
		switch (int(player.current_jump_frame)) {
		case 0:
			player.sprite.setTextureRect(IntRect(0, 87, 39, 44));
			break;
		case 1:
			player.sprite.setTextureRect(IntRect(39, 87, 39, 44));
			break;
		case 2:
			player.sprite.setTextureRect(IntRect(78, 87, 39, 45));
			break;
		case 3:
			player.sprite.setTextureRect(IntRect(117, 87, 39, 45));
			break;
		default:
			player.sprite.setTextureRect(IntRect(117, 87, 39, 45));
			break;
		}
	}
}

void AttackAnimation(Player& player, float game_step) {
	if (player.left_attack) {
		player.prev_state = LEFT;
		player.displacement = 0;
		player.right_attack = false;
		player.current_attack_frame += float(0.1 * game_step);
		switch (int(player.current_attack_frame)) {
		case 0:
			player.sprite.setTextureRect(IntRect(0 + 30, 44, -30, 44));
			break;
		case 1:
			player.sprite.setTextureRect(IntRect(30 + 24, 44, -24, 44));
			break;
		case 2:
			player.sprite.setTextureRect(IntRect(54 + 27, 44, -27, 44));
			break;
		case 3:
			player.displacement = -20;
			player.sprite.setTextureRect(IntRect(81 + 49, 44, -49, 44));
			break;
		case 4:
			player.displacement = -20;
			player.sprite.setTextureRect(IntRect(130 + 68, 44, -68, 44));
			break;
		case 5:
			player.sprite.setTextureRect(IntRect(198 + 37, 44, -37, 44));
			break;
		default:
			player.attack_occured = false;
			player.left_attack = false;
			player.current_attack_frame = 0.f;
			break;
		}
	}

	if (player.right_attack) {
		player.prev_state = RIGHT;
		player.displacement = 0;
		player.left_attack = false;
		switch (int(player.current_attack_frame)) {
		case 0:
			player.sprite.setTextureRect(IntRect(0, 44, 30, 44));
			player.displacement = 4;
			break;
		case 1:
			player.sprite.setTextureRect(IntRect(30, 44, 24, 44));
			player.displacement = 7;
			break;
		case 2:
			player.sprite.setTextureRect(IntRect(54, 44, 27, 44));
			player.displacement = 5;
			break;
		case 3:
			player.sprite.setTextureRect(IntRect(81, 44, 49, 44));
			player.displacement = 7;
			break;
		case 4:
			player.displacement = -7;
			player.sprite.setTextureRect(IntRect(130, 44, 68, 44));
			break;
		case 5:
			player.sprite.setTextureRect(IntRect(198, 44, 37, 44));
			break;
		default:
			player.attack_occured = false;
			player.right_attack = false;
			player.current_attack_frame = 0.f;
			break;
		}
		player.current_attack_frame += float(0.1 * game_step);
	}
}

void MoveAndStayAnimation(Player& player, float game_step) {
	switch (player.state) {
	case LEFT:
		player.prev_state = LEFT;
		//left
		if (!player.left_attack && !player.right_attack) {
			switch (int(player.current_move_frame)) {
			case 0:
				player.sprite.setTextureRect(IntRect(22, 0, -22, 42));
				break;
			case 1:
				player.sprite.setTextureRect(IntRect(23 + 32, 0, -32, 42));
				break;
			case 2:
				player.sprite.setTextureRect(IntRect(55 + 26, 0, -26, 42));
				break;
			case 3:
				player.sprite.setTextureRect(IntRect(81 + 20, 0, -20, 42));
				break;
			case 4:
				player.sprite.setTextureRect(IntRect(101 + 23, 0, -23, 42));
				break;
			case 5:
				player.sprite.setTextureRect(IntRect(124 + 32, 0, -32, 42));
				break;
			case 6:
				player.sprite.setTextureRect(IntRect(156 + 27, 0, -27, 42));
				break;
			case 7:
				player.sprite.setTextureRect(IntRect(183 + 22, 0, -22, 42));
				break;
			default:
				player.current_move_frame = 0.f;
				break;
			}
			player.current_move_frame += float(player.anim_speed * game_step);
		}
		break;
	case RIGHT:
		player.prev_state = RIGHT;
		//right
		if (!player.left_attack && !player.right_attack) {
			switch (int(player.current_move_frame)) {
			case 0:
				player.sprite.setTextureRect(IntRect(0, 0, 22, 42));
				break;
			case 1:
				player.sprite.setTextureRect(IntRect(23, 0, 32, 42));
				break;
			case 2:
				player.sprite.setTextureRect(IntRect(55, 0, 26, 42));
				break;
			case 3:
				player.sprite.setTextureRect(IntRect(81, 0, 20, 42));
				break;
			case 4:
				player.sprite.setTextureRect(IntRect(101, 0, 23, 42));
				break;
			case 5:
				player.sprite.setTextureRect(IntRect(124, 0, 32, 42));
				break;
			case 6:
				player.sprite.setTextureRect(IntRect(156, 0, 27, 42));
				break;
			case 7:
				player.sprite.setTextureRect(IntRect(183, 0, 22, 42));
				break;
			default:
				player.current_move_frame = 0.f;
				break;
			}
			player.current_move_frame += float(player.anim_speed * game_step);
		}
		break;
	case NONE:
		//none 
		if (player.prev_state == RIGHT) {
			player.sprite.setTextureRect(IntRect(34 * int(player.current_stay_frame), 132, 34, 41));
		}
		else {
			player.sprite.setTextureRect(IntRect(34 * int(player.current_stay_frame) + 34, 132, -34, 41));
		}
		player.current_stay_frame += float(player.anim_speed * game_step / 5);
		if (player.current_stay_frame > 2) {
			player.current_stay_frame = 0.f;
		}
		break;
	}
}

void PlayerAnimations(Player& player, const sf::Time& deltaTime) {
	float game_step = player.step * deltaTime.asSeconds();
	MoveAndStayAnimation(player, game_step);
	AttackAnimation(player, game_step);
	JumpAnimation(player, game_step);
	GravityAnimation(player);
}
