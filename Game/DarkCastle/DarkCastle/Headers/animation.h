#pragma once
#include "consts_and_enums.h"
#include "frame.h"
#include "game_sounds.h"


struct Animation {
	bool left_attack;
	bool right_attack;
	float current_attack_frame;
	float current_move_frame;
	float current_jump_frame;
	float current_stay_frame;
	float max_attack_frame;
	float max_move_frame;
	float max_jump_frame;
	float max_stay_frame;
	float anim_speed;
	float anim_stay_speed;
	Frame * frame;
};

Animation* CreateAnimation(Type type, std::vector<json_spirit::Pair> & int_rects);

void AnimationInit(Animation & animation, Type type, std::vector<json_spirit::Pair> & int_rects);

void DestroyAnimation(Animation *& animation);

void GravityAnimation(Animation & animation);

void JumpAnimation(Animation & animation, float game_step);

void AttackAnimation(Animation& animation, Type type, float game_step);

void MoveAndStayAnimation(Animation & animation, State state, Type type, float game_step);

void DisableAttack(Animation & animation);

void CheckMoveReset(Animation& animation);

void CheckAttackReset(Animation& animation);

void CheckJumpReset(Animation& animation);

void CheckStayReset(Animation& animation);

void FlipRectHoriz(sf::IntRect & rect);

void CheckStayFlip(sf::Sprite & sprite, sf::IntRect & rect);


