#include <sstream>
#include "../Headers/enemy.h"
#include "math.h"
#include "../Headers/safe_delete.h"

using namespace sf;
using namespace std;

Enemy* CreateEnemy(Resourses & res, int number) {
	Enemy * enemy = new Enemy();
	EnemyInit(*enemy, SPEARMAN, res, number);
	return enemy;
}

void EnemyInit(Enemy& enemy, Type type, Resourses & res, int number) {
	enemy.type = type;
	enemy.fight = CreateFightLogic(type);
	enemy.hp_bar = CreateHpBar(type, *res.int_rects, enemy.fight->health_points, enemy.fight->max_health_points);
	enemy.movement = CreateMovement(type);
	enemy.ai = CreateAI(type);
	FloatRect rect = GetEnemyRectFromLvl(*res.lvl, type, number);
	enemy.visual = CreateVisual(type, rect, *res.int_rects);
	enemy.is_attacked = false;
	enemy.is_injured = false;
}

FloatRect GetEnemyRectFromLvl(Level& lvl, Type type, int number) {
	stringstream str_number;
	string enemy_type = TypeToString(type);
	str_number << number;
	return lvl.GetObject(enemy_type + str_number.str()).rect;
}

int GetEnemiesCount(Level& lvl, Type type) {
	switch (type) {
		case SPEARMAN:
			return lvl.GetMatchObjects(0, 8, "SPEARMAN").size();
		case SWORDSMAN:
			return lvl.GetMatchObjects(0, 9, "SWORDMAN").size();
		default:
			break;
	}
	return 0;
}


void ProcessEnemyEvents(Enemy& enemy, FloatRect& player_box) {
	Animation& anim = *enemy.visual->animation;
	FloatRect& enemy_box = *enemy.visual->rect;
	float enemy_box_right = enemy_box.left + enemy_box.width;
	float enemy_box_bottom = enemy_box.top + enemy_box.height;
	float player_box_right = player_box.left + player_box.width;
	float player_box_bottom = player_box.top + player_box.height;

	bool right_detect = player_box.left - enemy.ai->field_of_view <= enemy_box_right && player_box.left >= enemy_box.left;
	bool left_detect = player_box_right + enemy.ai->field_of_view >= enemy_box.left && player_box.left <= enemy_box.left;
	bool not_too_high = player_box_bottom > enemy_box.top && player_box_bottom <= enemy_box_bottom;
	if ((left_detect || right_detect) && not_too_high) {
		enemy.ai->state = DETECT;
	}
	else {
		enemy.ai->state = NOT_DETECT;
	}
	if (enemy.ai->state == DETECT) {
		if (left_detect) {
			enemy.movement->state = LEFT;
		}
		else if (right_detect) {
			enemy.movement->state = RIGHT;
		}
		else enemy.movement->state = NONE;
		bool close_from_left = enemy_box_right > player_box.left && enemy_box_right < player_box_right;
		bool close_from_right = enemy_box.left < player_box_right && enemy_box.left > player_box.left;
		if (close_from_left) {
			anim.right_attack = true;
			anim.left_attack = false;
			enemy.movement->state = NONE;
		}
		else if (close_from_right) {
			anim.left_attack = true;
			anim.right_attack = false;
			enemy.movement->state = NONE;
		}
	}
}

void EnemyUpdate(Enemy& enemy, const sf::Time& deltaTime, Level& level) {
	Movement& movement = *enemy.movement;
	Animation& animation = *enemy.visual->animation;
	sf::FloatRect& enemy_rect = *enemy.visual->rect;
	CheckMovementLogic(movement);
	AnimationsUpdate(enemy);

	enemy.visual->rect->left += movement.delta_x * deltaTime.asSeconds();
	enemy.visual->rect->top += movement.delta_y * deltaTime.asSeconds();

	CheckEnemyAndLevelCollision(enemy, level);

	movement.x_pos = enemy_rect.left + animation.frame->displacement;
	movement.y_pos = enemy_rect.top + enemy_rect.height;

	animation.frame->sprite.setOrigin(0, animation.frame->sprite.getGlobalBounds().height);
	animation.frame->sprite.setPosition(movement.x_pos, movement.y_pos);

	sf::FloatRect & enemy_bound = *enemy.visual->rect;
	HpBarUpdate(*enemy.hp_bar, enemy_bound, SPEARMAN, enemy.fight->health_points);
	//===================================================================================
	LogicAI & ai = *enemy.ai;
	if (movement.state == NONE) {
		ai.stay_time += deltaTime.asSeconds();
		if (int(ai.stay_time) >= ai.max_stay_time) {
			ai.stay_time = 0.f;
			if (movement.prev_state == RIGHT) {
				movement.state = LEFT;
			}
			else {
				movement.state = RIGHT;
			}
		}
	}
	if (abs(int(ai.current_distance)) >= ai.max_distance) {
		if (ai.current_distance < 0) {
			movement.prev_state = LEFT;
		}
		if (ai.current_distance > 0) {
			movement.prev_state = RIGHT;
		}
		ai.current_distance = 0.f;
		movement.state = NONE;
	}
	else {
		ai.current_distance += movement.delta_x * deltaTime.asSeconds();
	}
}

void AnimationsUpdate(Enemy& enemy) {
	Animation& animation = *enemy.visual->animation;
	State& state = enemy.movement->state;
	float game_step = enemy.movement->step * TimePerFrame.asSeconds();
	animation.frame->sprite.setColor(Color::White);
	MoveAndStayAnimation(animation, state, enemy.type, game_step);
	AttackAnimation(animation, enemy.type, game_step);
}

void ProcessCollision(Enemy& enemy, const Object& map_object) {
	Frame& frame = *enemy.visual->animation->frame;
	sf::FloatRect& enemy_rect = *enemy.visual->rect;
	Movement& movement = *enemy.movement;
	if (enemy_rect.intersects(map_object.rect)) {
		if (map_object.name == "trap") {
			enemy.fight->health_points = 0.f;
		}
		else if (map_object.name == "solid") {
			bool bottom_collision = enemy_rect.top + enemy_rect.height - 5 < map_object.rect.top;
			bool upper_collision = enemy_rect.top + 5 > map_object.rect.top + map_object.rect.height;

			if (movement.delta_y > 0 && bottom_collision) {
				enemy_rect.top = map_object.rect.top - enemy_rect.height + 1;
			}
			else if (movement.delta_y < 0 && upper_collision) {
				enemy_rect.top = map_object.rect.top + map_object.rect.height;
			}

			if (movement.delta_x < 0 && !upper_collision && !bottom_collision) {
				enemy_rect.left = map_object.rect.left + map_object.rect.width;
			}
			else if (movement.delta_x > 0 && !upper_collision && !bottom_collision) {
				enemy_rect.left -= enemy_rect.left + enemy_rect.width - map_object.rect.left;
			}
		}
	}
}

void CheckEnemyAndLevelCollision(Enemy& enemy, Level& level) {
	vector<Object> * map_objects = level.GetAllObjects();
	for (auto & obj : *map_objects)
	{
		ProcessCollision(enemy, obj);
	}
	/*for (size_t i = 0; i < map_objects.size(); i++) {
		
	}*/
}

void DestroyEnemy(Enemy *& enemy) {
	DestroyMovement(enemy->movement);
	DestroyFightLogic(enemy->fight);
	DestroyVisual(enemy->visual);
	DestroyAI(enemy->ai);
	DestroyHpBar(enemy->hp_bar);
	SafeDelete(enemy);
}
