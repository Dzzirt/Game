#include "../Headers/player.h"

using namespace sf;
using namespace std;


void ViewUpdate(sf::View& view, RenderWindow& window, const Movement& movement, const Level& level, float displacement) {


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

	view.setCenter(tempX, tempY);
}

sf::FloatRect GetPlayerRectFromLvl(Level& lvl) {
	return lvl.GetObject("player").rect;
}

void CheckPlayerAndLevelCollision(Player& player, const Level& level) {
	vector<Object> map_objects = level.GetAllObjects();
	for (int i = 0; i < map_objects.size(); i++) {
		PlayerLevelCollision(player, map_objects[i]);
	}
}

void PlayerLevelCollision(Player& player, const Object& map_object) {
	FloatRect& player_rect = *player.visual->rect;
	Movement& movement = *player.movement;
	Jump& jump = *player.jumping;
	if (player_rect.intersects(map_object.rect)) {
		if (map_object.name == "trap") {

			jump.in_jump = true;
			player.fight->health_points -= 10.f;
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

Player* CreatePlayer(Level& level) {
	Player* player = new Player();
	PlayerInit(*player, level);
	return player;
}

void PlayerInit(Player& player, Level& level) {
	player.fight = new FightLogic();
	player.movement = new Movement();
	player.jumping = new Jump();
	player.visual = new Visual();
	player.view = new View();
	player.view->reset(sf::FloatRect(0, 0, WindowWidth, WindowHeight));
	FloatRect rect = GetPlayerRectFromLvl(level);
	VisualInit(*player.visual, PLAYER, rect);
	JumpingInit(*player.jumping, PLAYER);
	FightLogicInit(*player.fight, PLAYER);
	MovementInit(*player.movement, PLAYER);
}

void DestroyPlayer(Player*& player) {
	DestroyFightLogic(player->fight);
	DestroyMovement(player->movement);
	DestroyJump(player->jumping);
	DestroyVisual(player->visual);
	delete player->view;
	delete player;
}

void PlayerUpdate(Player& player, const Level& level, const sf::Time& deltaTime) {
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
	MoveAndStayAnimation(animation, state, game_step);
	AttackAnimation(animation, game_step);
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

void ProcessPlayerEvents(RenderWindow& window, Player& player, Level& level) {
	Jump& jump = *player.jumping;
	View& view = *player.view;
	Movement& movement = *player.movement;
	Animation& animation = *player.visual->animation;
	FloatRect sprite_bounds = animation.frame->sprite.getGlobalBounds();
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
			view.setSize(event.size.width, event.size.height);
			int map_height = level.height * level.tileHeight;
			int map_width = level.width * level.tileWidth;
			cout << map_height / float(event.size.height * event.size.height / WindowHeight) << endl;
			if (map_height < map_width) {
				if (unsigned int(map_height) < event.size.height) {
					view.zoom(map_height / float(event.size.height));
				}
			}
			else {
				if (unsigned int(map_width) < event.size.width) {
					view.zoom(map_width / event.size.width);
				}
			}

		}
	}
}
