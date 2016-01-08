#include "../Headers/player.h"
#include <boost/bind/bind.hpp>
#include "../Headers/safe_delete.h"

using namespace sf;
using namespace std;


Player* CreatePlayer(Resourses& res) {
	Player* player = new Player();
	PlayerInit(*player, res);
	return player;
}

FloatRect GetPlayerRectFromLvl(Level& lvl) {
	return lvl.GetObject("player").rect;
}

void PlayerInit(Player& player, Resourses& res) {
	player.fight = CreateFightLogic(PLAYER);
	player.hp_bar = CreateHpBar(PLAYER, *res.int_rects, player.fight->health_points, player.fight->max_health_points);
	player.movement = CreateMovement(PLAYER);
	player.jumping = CreateJump(PLAYER);
	FloatRect rect = GetPlayerRectFromLvl(*res.lvl);
	player.visual = CreateVisual(PLAYER, rect, *res.int_rects);
	player.is_map_complete = false;
	player.is_injured = false;
}

void CheckPlayerAndLevelCollision(Player& player, Level& level) {
	vector<Object> * map_objects = level.GetAllObjects();
	for (auto & obj : *map_objects)
	{
		PlayerLevelCollision(player, obj);
	}
}

void PlayerLevelCollision(Player & player, const Object & map_object) {
	FloatRect& player_rect = *player.visual->rect;
	Movement& movement = *player.movement;
	Jump& jump = *player.jumping;
	if (player_rect.intersects(map_object.rect)) {
		if (map_object.name == "exit") {
			player.is_map_complete = true;
		}
		else if (map_object.name == "trap") {
			jump.in_jump = true;
			player.is_injured = true;
			player.fight->health_points -= 10.f;
			if (player.fight->health_points <= 0) {
				player.fight->is_dead = true;
			}
		}
		else if (map_object.name == "solid") {
			bool bottom_collision = player_rect.top + player_rect.height - 5 < map_object.rect.top;
			bool upper_collision = player_rect.top + 5 > map_object.rect.top + map_object.rect.height;

			if (movement.delta_y > 0 && bottom_collision) {
				jump.on_ground = true;
				player_rect.top = map_object.rect.top - player_rect.height;
			}
			else if (movement.delta_y < 0 && upper_collision) {
				player_rect.top = map_object.rect.top + map_object.rect.height;
				jump.in_jump = false;
			}

			if (movement.delta_x < 0 && !upper_collision && !bottom_collision) {
				player_rect.left = map_object.rect.left + map_object.rect.width;
			}
			else if (movement.delta_x > 0 && !upper_collision && !bottom_collision) {
				player_rect.left -= player_rect.left + player_rect.width - map_object.rect.left;
			}
		}

	}
}

void PlayerUpdate(Player & player, Level & level, const sf::Time& deltaTime) {
	Movement& movement = *player.movement;
	Frame& player_frame = *player.visual->animation->frame;
	Jump& jump = *player.jumping;
	Animation& animation = *player.visual->animation;
	FloatRect& player_rect = *player.visual->rect;
	CheckMovementLogic(movement);
	CheckGravityLogic(jump, movement, deltaTime);
	CheckJumpLogic(jump, movement, animation);
	AnimationsUpdate(player);

	player_rect.left += movement.delta_x * deltaTime.asSeconds();
	player_rect.top += movement.delta_y * deltaTime.asSeconds();

	CheckPlayerAndLevelCollision(player, level);

	movement.x_pos = player_rect.left + player_frame.displacement;
	movement.y_pos = player_rect.top + player_rect.height;

	player_frame.sprite.setOrigin(0, player_frame.sprite.getGlobalBounds().height);
	player_frame.sprite.setPosition(movement.x_pos, movement.y_pos);


}

void AnimationsUpdate(Player& player) {
	Animation& animation = *player.visual->animation;
	bool& on_ground = player.jumping->on_ground;
	bool& in_jump = player.jumping->in_jump;
	State& state = player.movement->state;
	float game_step = player.movement->step * TimePerFrame.asSeconds();
	animation.frame->displacement = 0;
	animation.frame->sprite.setColor(Color::White);
	MoveAndStayAnimation(animation, state, PLAYER, game_step);
	AttackAnimation(animation, PLAYER, game_step);
	if (in_jump) {
		JumpAnimation(animation, game_step);
	}
	if (!on_ground && !in_jump) {
		GravityAnimation(animation);
	}
}

void CheckGravityLogic(Jump& jump, Movement& movement, const sf::Time& deltaTime) {
	if (!jump.in_jump) {
		movement.delta_y = ForceOfGravity;
	}
}

void ProcessPlayerEvents(RenderWindow& window, Player& player, GameSounds& game_sounds, View& view) {
	Jump& jump = *player.jumping;
	Movement& movement = *player.movement;
	Animation& animation = *player.visual->animation;
	FloatRect sprite_bounds = animation.frame->sprite.getGlobalBounds();
	if (Keyboard::isKeyPressed(Keyboard::Space) && jump.on_ground) {
		jump.in_jump = true;
		PlaySounds(JUMP, *game_sounds.sounds, *game_sounds.sound_buffers);
	}
	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		movement.state = LEFT;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		movement.state = RIGHT;
	}
	else {
		movement.state = NONE;
	}
	if (Mouse::isButtonPressed(Mouse::Left) && !jump.in_jump) {
		if (!animation.left_attack && !animation.right_attack) {
			PlaySounds(MISS, *game_sounds.sounds, *game_sounds.sound_buffers);
		}

		const float mouse_global_x = Mouse::getPosition(window).x + view.getCenter().x - (window.getSize().x / 2);
		if (mouse_global_x > sprite_bounds.left + sprite_bounds.width / 2.f) {
			animation.right_attack = true;
		}
		if (mouse_global_x < sprite_bounds.left + sprite_bounds.width / 2.f) {
			animation.left_attack = true;

		}

	}
}

void DrawPlayer(Player & player, RenderWindow &window)
{
	VisualHpBar& player_hp = *player.hp_bar->visual_hp;
	Sprite& player_sprite = player.visual->animation->frame->sprite;
	window.draw(player_sprite);
	window.draw(player_hp.bar_sprite);
	window.draw(player_hp.strip_sprite);
}

void DestroyPlayer(Player*& player) {
	DestroyFightLogic(player->fight);
	DestroyMovement(player->movement);
	DestroyJump(player->jumping);
	DestroyVisual(player->visual);
	DestroyHpBar(player->hp_bar);
	SafeDelete(player);
}
