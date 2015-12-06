#include "../Headers/animation.h"

using namespace sf;

Animation* CreateAnimation(Type type, std::vector<json_spirit::Pair> & int_rects) {
	Animation* animation = new Animation();
	AnimationInit(*animation, type, int_rects);
	return animation;
}

void AnimationInit(Animation& animation, Type type, std::vector<json_spirit::Pair> & int_rects) {
	animation.frame = CreateFrame(type, int_rects);
	animation.left_attack = false;
	animation.right_attack = false;
	animation.is_injured = false;
	animation.current_attack_frame = 0.f;
	animation.current_move_frame = 0.f;
	animation.current_jump_frame = 0.f;
	animation.current_stay_frame = 0.f;
	switch (type) {
		case PLAYER:
			animation.anim_speed = 0.07f;
			animation.anim_stay_speed = 0.014f;
			animation.max_attack_frame = 6.f;
			animation.max_move_frame = 8.f;
			animation.max_jump_frame = 4.f;
			animation.max_stay_frame = 2.f;
			break;
		case SPEARMAN:
			animation.anim_speed = 0.1f;
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

void DestroyAnimation(Animation& animation) {
	DestroyFrame(*animation.frame);
	delete &animation;
}

void GravityAnimation(Animation& animation) {
	Frame& frame = *animation.frame;
	IntRect& rect = animation.frame->rect->gravity;
	int injured_y = 0;
	// Disable attack
	DisableAttack(animation);
	//
	if (animation.is_injured) {
		injured_y = PlayerInjuredY;
	}
	frame.sprite.setTextureRect(IntRect(rect.left, rect.top + injured_y, rect.width, rect.height));

}


void JumpAnimation(Animation& animation, float game_step) {
	Frame& frame = *animation.frame;
	IntRect jump_rect = frame.rect->jump;
	int injured_y = 0;
	animation.current_jump_frame += float(0.07 * game_step);
	CheckJumpReset(animation);
	jump_rect.left *= int(animation.current_jump_frame);
	if (animation.is_injured) {
		injured_y = PlayerInjuredY;
	}
	frame.sprite.setTextureRect(IntRect(jump_rect.left, jump_rect.top + injured_y, jump_rect.width, jump_rect.height));
}

void AttackAnimation(Animation& animation, Type type, float game_step) {
	Frame& frame = *animation.frame;
	IntRect atk_rect = frame.rect->attack;
	float& atk_frame = animation.current_attack_frame;
	int injured_y = 0;
	if (animation.is_injured) {
		if (type == PLAYER) {
			injured_y = PlayerInjuredY;
		}
		else if (type == SPEARMAN) {
			injured_y = SpearmanInjuredY;
		} 
	}
	if (animation.left_attack) {
		if (type == SPEARMAN) {
			switch (int(atk_frame)) {
			case 0: frame.displacement = 0 - 7;
				break;
			case 1: frame.displacement = -3 - 7;
				break;
			case 2: frame.displacement = -5 - 7;
				break;
			case 3: frame.displacement = -3 - 7;
				break;
			case 4: frame.displacement = 0 - 7;
				break;
			case 5: frame.displacement = -2 - 7;
				break;
			case 6: frame.displacement = -2 - 7;
				break;
			}
		}
			if (type == PLAYER) {
				frame.displacement = -45;
			}
			animation.right_attack = false;
			atk_frame += float(animation.anim_speed * game_step);
			CheckAttackReset(animation);
			atk_rect.left *= int(atk_frame);
			FlipRectHoriz(atk_rect);
			frame.sprite.setTextureRect(IntRect(atk_rect.left, atk_rect.top + injured_y, atk_rect.width, atk_rect.height));
		}
	
		if (animation.right_attack) {
			if (type == SPEARMAN) {
				switch (int(atk_frame)) {
				case 0: frame.displacement = -13;
					break;
				case 1: frame.displacement = -10;
					break;
				case 2: frame.displacement = -8;
					break;
				case 3: frame.displacement = -10;
					break;
				case 4: frame.displacement = -13;
					break;
				case 5: frame.displacement = -11;
					break;
				case 6: frame.displacement = -11;
					break;
				}
			}
				animation.left_attack = false;
				atk_frame += float(animation.anim_speed * game_step);
				atk_rect.left *= int(atk_frame);
				if (atk_frame < animation.max_attack_frame) {
					frame.sprite.setTextureRect(IntRect(atk_rect.left, atk_rect.top + injured_y, atk_rect.width, atk_rect.height));
				}
				CheckAttackReset(animation);
			}
}
	

void MoveAndStayAnimation(Animation& animation, State state, Type type, float game_step) {
	Frame& frame = *animation.frame;
	IntRect move_rect = frame.rect->move;
	IntRect stay_rect = frame.rect->stay;
	frame.displacement = 0;
	int injured_y = 0;
	if (animation.is_injured) {
		if (type == PLAYER) {
			injured_y = PlayerInjuredY;
		}
		else if (type == SPEARMAN) {
			injured_y = SpearmanInjuredY;
		}
	}
	float& move_frame = animation.current_move_frame;
	switch (state) {
		case LEFT:
			move_frame += float(animation.anim_speed * game_step);
			CheckMoveReset(animation);
			move_rect.left *= int(move_frame);
			FlipRectHoriz(move_rect);
			frame.sprite.setTextureRect(IntRect(move_rect.left, move_rect.top + injured_y, move_rect.width, move_rect.height));
			break;
		case RIGHT:
			move_frame += float(animation.anim_speed * game_step);
			CheckMoveReset(animation);
			move_rect.left *= int(move_frame);
			frame.sprite.setTextureRect(IntRect(move_rect.left, move_rect.top + injured_y, move_rect.width, move_rect.height));
			break;
		case NONE:
			float& stay_frame = animation.current_stay_frame;
			stay_frame += float(animation.anim_stay_speed * game_step);
			CheckStayReset(animation);
			stay_rect.left *= int(stay_frame);
			CheckStayFlip(frame.sprite, stay_rect);
			frame.sprite.setTextureRect(IntRect(stay_rect.left, stay_rect.top + injured_y, stay_rect.width, stay_rect.height));
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
