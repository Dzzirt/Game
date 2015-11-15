#include "../Headers/animation.h"

using namespace sf;


void AnimationInit(Animation& animation, Type type) {
	animation.frame = new Frame();
	FrameInit(*animation.frame, type);
	animation.left_attack = false;
	animation.right_attack = false;
	animation.current_attack_frame = 0.f;
	animation.current_move_frame = 0.f;
	animation.current_jump_frame = 0.f;
	animation.current_stay_frame = 0.f;
	switch (type) {
		case PLAYER:
			animation.anim_speed = 0.07;
			animation.anim_stay_speed = 0.014;
			animation.max_attack_frame = 6.f;
			animation.max_move_frame = 8.f;
			animation.max_jump_frame = 4.f;
			animation.max_stay_frame = 2.f;
			break;
		case SPEARMAN:
			animation.anim_speed = 0.1;
			animation.max_attack_frame = 7.f;
			animation.max_move_frame = 8.f;
			animation.max_jump_frame = 0.f;
			animation.max_stay_frame = 0.f;
			break;
		case SWORDSMAN:

			break;
		default:
			break;
	}
}

void GravityAnimation(Animation& animation) {
	Frame& frame = *animation.frame;
	IntRect& rect = animation.frame->rect->gravity;
	// Disable attack
	DisableAttack(animation);
	//
	frame.sprite.setTextureRect(rect);
}


void JumpAnimation(Animation& animation, float game_step) {
	Frame& frame = *animation.frame;
	IntRect jump_rect = frame.rect->jump;
	animation.current_jump_frame += float(0.07 * game_step);
	CheckJumpReset(animation);
	jump_rect.left *= int(animation.current_jump_frame);
	frame.sprite.setTextureRect(jump_rect);
}

void AttackAnimation(Animation& animation, float game_step) {
	Frame& frame = *animation.frame;
	IntRect atk_rect = frame.rect->attack;
	float& atk_frame = animation.current_attack_frame;
	if (animation.left_attack) {
		frame.displacement = -41;
		animation.right_attack = false;
		atk_frame += float(animation.anim_speed * game_step);
		CheckAttackReset(animation);
		atk_rect.left *= int(atk_frame);
		FlipRectHoriz(atk_rect);
		frame.sprite.setTextureRect(atk_rect);

	}
	if (animation.right_attack) {
		animation.left_attack = false;
		atk_frame += float(animation.anim_speed * game_step);
		atk_rect.left *= int(atk_frame);
		if (atk_frame < animation.max_attack_frame) {
			frame.sprite.setTextureRect(atk_rect);
		}
		CheckAttackReset(animation);
	}
}

void MoveAndStayAnimation(Animation& animation, State state, float game_step) {
	Frame& frame = *animation.frame;
	IntRect move_rect = frame.rect->move;
	IntRect stay_rect = frame.rect->stay;
	float& move_frame = animation.current_move_frame;
	switch (state) {
		case LEFT:
			move_frame += float(animation.anim_speed * game_step);
			CheckMoveReset(animation);
			move_rect.left *= int(move_frame);
			FlipRectHoriz(move_rect);
			frame.sprite.setTextureRect(move_rect);
			break;
		case RIGHT:
			move_frame += float(animation.anim_speed * game_step);
			CheckMoveReset(animation);
			move_rect.left *= int(move_frame);
			frame.sprite.setTextureRect(move_rect);
			break;
		case NONE:
			float& stay_frame = animation.current_stay_frame;
			stay_frame += float(animation.anim_stay_speed * game_step);
			CheckStayReset(animation);
			stay_rect.left *= int(stay_frame);
			CheckStayFlip(frame.sprite, stay_rect);
			frame.sprite.setTextureRect(stay_rect);
			break;
	}
}

void DisableAttack(Animation& animation) {
	animation.left_attack = false;
	animation.right_attack = false;
	animation.frame->displacement = 0;
}

void CheckMoveReset(Animation& animation) {
	if (animation.current_move_frame > animation.max_move_frame) {
		animation.current_move_frame -= animation.max_move_frame;
	}
}

void CheckAttackReset(Animation& animation) {
	if (animation.current_attack_frame > animation.max_attack_frame) {
		animation.left_attack = false;
		animation.right_attack = false;
		animation.current_attack_frame -= animation.max_attack_frame;
	}
}

void CheckStayReset(Animation& animation) {
	if (animation.current_stay_frame > animation.max_stay_frame) {
		animation.current_stay_frame -= animation.max_stay_frame;
	}
}

void CheckJumpReset(Animation& animation) {
	if (animation.current_jump_frame > animation.max_jump_frame) {
		animation.current_jump_frame = 1;
	}
}

void FlipRectHoriz(sf::IntRect& rect) {
	rect.left += rect.width;
	rect.width *= -1;
}

void CheckStayFlip(Sprite& sprite, IntRect& rect) {
	if (sprite.getTextureRect().width < 0) {
		FlipRectHoriz(rect);
	}
}
