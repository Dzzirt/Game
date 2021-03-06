#include "../Headers/animation.h"
#include "../Headers/safe_delete.h"
#include "../Headers/game_rand.h"
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
	animation.current_attack_frame = 0.f;
	animation.current_move_frame = 0.f;
	animation.current_jump_frame = 0.f;
	animation.current_stay_frame = 0.f;
	FrameRects & rects = *animation.frame->rect;
	animation.atk_rect_pack_num = GetRandomInt(0, rects.attack_rects.size() - 1);
	animation.current_attack_rect = rects.attack_rects[animation.atk_rect_pack_num];

	switch (type) {
		case PLAYER:
			animation.anim_speed = 0.06f;
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
		case JELLY_BOSS:
			animation.anim_speed = 0.05f;
			animation.max_attack_frame = 6.f;
			animation.max_move_frame = 12.f;
			animation.max_jump_frame = 0.f;
			animation.max_stay_frame = 0.f;
			break;
		case JELLY:
			animation.anim_speed = 0.05f;
			animation.max_attack_frame = 6.f;
			animation.max_move_frame = 12.f;
			animation.max_jump_frame = 0.f;
			animation.max_stay_frame = 0.f;
			break;
		default:
			break;
	}
}

void DestroyAnimation(Animation *& animation) {
	DestroyFrame(animation->frame);
	SafeDelete(animation);
}

void GravityAnimation(Animation& animation) {
	Frame& frame = *animation.frame;
	IntRect& rect = animation.frame->rect->gravity;
	int injured_y = 0;
	DisableAttack(animation);
	frame.sprite.setTextureRect(IntRect(rect.left, rect.top + injured_y, rect.width, rect.height));

}


void JumpAnimation(Animation& animation, float game_step) {
	Frame& frame = *animation.frame;
	IntRect jump_rect = frame.rect->jump;
	int injured_y = 0;
	animation.current_jump_frame += float(0.07 * game_step);
	CheckJumpReset(animation);
	jump_rect.left *= int(animation.current_jump_frame);
	frame.sprite.setTextureRect(jump_rect);
}

void AttackAnimation(Animation& animation, Type type, float game_step) {
	Frame& frame = *animation.frame;
	float& atk_frame = animation.current_attack_frame;
	sf::IntRect atk_rect = animation.current_attack_rect;
	int injured_y = 0;
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
		else if (type == JELLY_BOSS )
		{
			
			if (animation.atk_rect_pack_num == 0) {
				frame.displacement = -72;
			}
			if (animation.atk_rect_pack_num == 1) {
				frame.displacement = -50;
			}
			if (animation.atk_rect_pack_num == 2) {
				frame.displacement = -48;
			}

		}
		else if (type == JELLY)
		{
				frame.displacement = -50;
		}
		else if (type == PLAYER) {
			frame.displacement = -45;
		}
		animation.right_attack = false;
		atk_frame += float(animation.anim_speed * game_step);
		CheckAttackReset(animation);
		atk_rect.left *= int(atk_frame);
		FlipRectHoriz(atk_rect);
		frame.sprite.setTextureRect(atk_rect);
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
					frame.sprite.setTextureRect(atk_rect);
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
			CheckStayFlip(frame.sprite, stay_rect, type, frame.displacement);
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
		FrameRects & rects = *animation.frame->rect;
		animation.atk_rect_pack_num = GetRandomInt(0, rects.attack_rects.size() - 1);
		animation.current_attack_rect = rects.attack_rects[animation.atk_rect_pack_num];
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

void CheckStayFlip(sf::Sprite & sprite, sf::IntRect & rect, Type type, float & displacement) {
	if (sprite.getTextureRect().width < 0) {
		if (type == JELLY)
		{
			displacement = -30;
		}
		FlipRectHoriz(rect);
	}
}
