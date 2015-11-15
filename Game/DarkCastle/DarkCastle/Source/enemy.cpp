#include <sstream>
#include "../Headers/enemy.h"

void EnemyInit(Enemy & enemy, Type type, sf::FloatRect & rect) {
	enemy.visual = new Visual();
	enemy.logic = new Logic();
	VisualInit(*enemy.visual, type, rect);
	LogicInit(*enemy.logic, type);
}

sf::FloatRect GetEnemyRectFromLvl(Level & lvl, Type type, int number) {
	std::stringstream str_number;
	std::string enemy_type = TypeToString(type);
	str_number << number;
	return lvl.GetObject(enemy_type + str_number.str()).rect;
}

int GetEnemiesCount(Level& lvl, Type type) {
	switch (type) {
	case SPEARMAN:
		return lvl.GetMatchObjects(0, 8, "spearman").size();
	case SWORDSMAN:
		return lvl.GetMatchObjects(0, 9, "swordsman").size();
	default:
		break;
	}
	return 0;
}


void EnemyUpdate(Enemy& enemy, const sf::Time& deltaTime) {
	Movement & movement = *enemy.logic->movement;
	Animation & animation = *enemy.visual->animation;
	sf::FloatRect & enemy_rect = *enemy.visual->rect;
	CheckMovementLogic(movement);
	// Box & Sprite steps

	AnimationsUpdate(enemy);

	enemy.visual->rect->left += movement.delta_x;
	enemy.visual->rect->top += movement.delta_y;

	movement.x_pos = enemy_rect.left;// +enemy.displacement;
	movement.y_pos = enemy_rect.top + enemy_rect.height;

	animation.frame->sprite.setOrigin(0, animation.frame->sprite.getGlobalBounds().height);
	animation.frame->sprite.setPosition(movement.x_pos, movement.y_pos);
	sf::FloatRect enemy_bound = enemy.visual->animation->frame->sprite.getGlobalBounds();
	HpBarUpdate(*enemy.logic->fight, enemy_bound, SPEARMAN);
}

void AnimationsUpdate(Enemy& enemy) {
	Animation & animation = *enemy.visual->animation;
	State & state = enemy.logic->movement->state;
	float game_step = enemy.logic->movement->step * TimePerFrame.asSeconds();
	MoveAndStayAnimation(animation, state, game_step);
	AttackAnimation(animation, game_step);
}

void EnemyLevelCollision(Enemy& enemy, const Object & map_object) {
	sf::FloatRect& enemy_rect = *enemy.visual->rect;
	Movement & movement = *enemy.logic->movement;
	if (enemy_rect.intersects(map_object.rect)) {
		if (map_object.name == "trap") {
			enemy.logic->fight->health_points = 0.f;
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