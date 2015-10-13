#include "enemy.h"
#include "map.h"


void CheckEnemyCollisions(Enemy & enemy) {
	for (size_t i = 0; i < enemy.obj.size(); i++) {
		sf::FloatRect & map_bounds = enemy.obj[i].rect;
		sf::FloatRect enemy_bounds = enemy.sprite.getGlobalBounds();
		//std::cout << game.lvl.GetObject("enemy").rect.left;
		//проходимся по объектамs

		if (enemy_bounds.intersects(enemy.obj[i].rect))//проверяем пересечение игрока с объектом
		{

			if (enemy.obj[i].name == "solid") {
				bool upper_collision = false;
				bool bottom_collision = false;
				bool enemy_higher_than_object = enemy_bounds.top + enemy_bounds.height - 4 < map_bounds.top;
				bool enemy_less_than_object = enemy_bounds.top + 4 > map_bounds.top + map_bounds.height;

				if (enemy.y_accel > 0 && enemy_higher_than_object) { // Check upper collision 
					enemy.y_pos = map_bounds.top - enemy_bounds.height;
					upper_collision = true;
				}
				else if (enemy.y_accel < 0 && enemy_less_than_object) { // Check bottom collision 
					enemy.y_pos = map_bounds.top + map_bounds.height;
					bottom_collision = true;
					enemy.jump = false;
				}

				if (enemy.x_accel < 0 && !upper_collision && !bottom_collision) { // Check collision with left side 
					enemy.x_pos = map_bounds.left + map_bounds.width;
				}
				else if (enemy.x_accel > 0 && !upper_collision && !bottom_collision) { // Check collision with right side
					enemy.x_pos -= enemy_bounds.left + enemy_bounds.width - map_bounds.left;
				}
			}
		}
	}
	enemy.x_accel = 0;
	enemy.y_accel = 0;
}

void EnemyUpdate(Enemy & enemy, const sf::Time& deltaTime) {
	switch (enemy.state) {
	case LEFT:
		enemy.x_accel = -enemy.step;
		break;
	case RIGHT:
		enemy.x_accel = enemy.step;
		break;
	case NONE:
		break;
	}
	// Jump

	if (enemy.jump && enemy.jump_height_counter < enemy.max_jump) {
		enemy.jump_height_counter += enemy.step * deltaTime.asSeconds() * JumpingSpeedCoef;
		enemy.y_accel = -enemy.step;
	}
	else {
		enemy.jump = false;
		enemy.jump_height_counter = 0.f;
	}

	// Gravity

	if (!enemy.on_ground && !enemy.jump) {
		enemy.y_accel = enemy.step;
	}
	enemy.x_pos += enemy.x_accel * deltaTime.asSeconds();
	enemy.y_pos += enemy.y_accel * deltaTime.asSeconds();
	enemy.sprite.setPosition(enemy.x_pos, enemy.y_pos);
	CheckEnemyCollisions(enemy);
	enemy.sprite.setPosition(enemy.x_pos, enemy.y_pos);
}