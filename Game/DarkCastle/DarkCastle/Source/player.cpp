#include "../Headers/player.h"

using namespace sf;
using namespace std;


void ViewUpdate(sf::View& view, RenderWindow & window, const Movement & movement, const Level & level, float displacement) {
	unsigned int window_x = window.getSize().x;
	unsigned int window_y = window.getSize().y;

	float left_right_border = view.getSize().x / 2;
	float up_down_border = view.getSize().y / 2;
	int map_height = level.height * level.tileHeight;
	int map_width = level.width * level.tileWidth;

	float x_pos = movement.x_pos - displacement;
	float y_pos = movement.y_pos;
	float tempX = x_pos;
	float tempY = y_pos;

	if (x_pos < left_right_border) {
		tempX = left_right_border;
	}
	if (y_pos > map_height - up_down_border) {
		tempY = map_height - up_down_border;
	}
	if (x_pos > map_width - left_right_border) {
		tempX = map_width - left_right_border;
	}
	if (y_pos < up_down_border) {
		tempY = up_down_border;
	}

	if (map_height < map_width) {
		if (unsigned int(map_height) < window_y) {
			view.zoom(map_height / float(window_y));
		}
	}
	else {
		if (unsigned int(map_width) < window_x) {
			view.zoom(map_width / window_x);
		}
	}
	view.setCenter(tempX, tempY);
}

sf::FloatRect GetPlayerRectFromLvl(Level& lvl) {
	return lvl.GetObject("player").rect;
}

void PlayerLevelCollision(Player& player, const Object & map_object) {
	FloatRect& player_rect = *player.visual->rect;
	Movement & movement = *player.logic->movement;
	Jump & jump = *player.jumping;
	if (player_rect.intersects(map_object.rect)) {
		if (map_object.name == "trap") {

			jump.in_jump = true;
			player.logic->fight->health_points -= 10.f;
		}
		else if (map_object.name == "solid") {
			bool bottom_collision = player_rect.top + player_rect.height - 5 < map_object.rect.top;
			bool upper_collision = player_rect.top + 5 > map_object.rect.top + map_object.rect.height;

			if (movement.delta_y > 0 && bottom_collision) {
				jump.on_ground = true;
				player_rect.top = map_object.rect.top - player_rect.height - 1;
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

void PlayerInit(Player & player, sf::FloatRect & rect) {
	player.logic = new Logic();
	player.jumping = new Jump();
	player.visual = new Visual();
	player.view = new View();
	player.view->reset(sf::FloatRect(0, 0, WindowWidth, WindowHeight));
	VisualInit(*player.visual, PLAYER, rect);
	LogicInit(*player.logic, PLAYER);
	JumpingInit(*player.jumping, PLAYER);
}

void PlayerUpdate(Player & player, const sf::Time& deltaTime) {
	Movement & movement = *player.logic->movement;
	Jump & jump = *player.jumping;
	Animation & animation = *player.visual->animation;
	FloatRect & player_rect = *player.visual->rect;
	CheckMovementLogic(movement);
	CheckGravityLogic(jump, movement, deltaTime);
	CheckJumpLogic(jump, movement, animation);
	AnimationsUpdate(player);

	player_rect.left += movement.delta_x * deltaTime.asSeconds();
	player_rect.top += movement.delta_y * deltaTime.asSeconds();

	movement.x_pos = player_rect.left + animation.frame->displacement;
	movement.y_pos = player_rect.top + player_rect.height;

	animation.frame->sprite.setOrigin(0, animation.frame->sprite.getGlobalBounds().height);
	animation.frame->sprite.setPosition(movement.x_pos, movement.y_pos);

	PlayerHpBarUpdate(*player.logic->fight, *player.view);
}

void AnimationsUpdate(Player& player) {
	Animation & animation = *player.visual->animation;
	bool & on_ground = player.jumping->on_ground;
	bool & in_jump = player.jumping->in_jump;
	State & state = player.logic->movement->state;
	float game_step = player.logic->movement->step * TimePerFrame.asSeconds();
	animation.frame->displacement = 0;
	MoveAndStayAnimation(animation, state, game_step);
	AttackAnimation(animation, game_step);
	if (in_jump) {
		JumpAnimation(animation, game_step);
	}
	if (!on_ground && !in_jump) {
		GravityAnimation(animation);
	}
}

void CheckGravityLogic(Jump & jump, Movement & movement, const sf::Time& deltaTime) {
	if (!jump.in_jump) {
		movement.delta_y = ForceOfGravity;
	}
}

void ProcessPlayerEvents(RenderWindow& window, Player & player) {
	Jump & jump = *player.jumping;
	View& view = *player.view;
	Movement & movement = *player.logic->movement;
	Animation & animation = *player.visual->animation;
	FloatRect  sprite_bounds = animation.frame->sprite.getGlobalBounds();
	Event event;

	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Space) && jump.on_ground) {
			jump.in_jump = true;
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
			const float mouse_global_x = Mouse::getPosition(window).x + view.getCenter().x - (window.getSize().x / 2);
			if (mouse_global_x > sprite_bounds.left + sprite_bounds.width / 2.f) {
				animation.right_attack = true;

			}
			if (mouse_global_x < sprite_bounds.left + sprite_bounds.width / 2.f) {
				animation.left_attack = true;

			}

		}
		if (event.type == Event::Closed) {
			window.close();
		}
		else if (event.type == Event::Resized) {
			view.setSize(float(event.size.width), float(event.size.height));
			view.zoom(WindowWidth / event.size.width);

		}
	}
}



