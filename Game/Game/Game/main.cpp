#include "game.h"


using namespace sf;

const Time TimePerFrame = seconds(1.f / 60.f);
const float STEP = 200.f;



int main() {
	RenderWindow window(VideoMode(800, 600), "From the Shadow of Underdark");
	Game* game = new Game();
	GameInit(*game);
	View* view = new View();
	view->reset(FloatRect(0, 0, ViewWidth, ViewHeight));

	Clock clock;
	Time time_since_last_update = Time::Zero;

	while (window.isOpen()) {
		ProcessEvents(window, *game->player, *view);
		time_since_last_update += clock.restart();
		while (time_since_last_update > TimePerFrame) {
			time_since_last_update -= TimePerFrame;
			PlayerUpdate(*game->player, TimePerFrame);
			CheckCollisions(*game);
			GetPlayerCoordinateForView(*view, game->player->x_pos + 30, game->player->y_pos + 45);
			
		}
		window.setView(*view);
		
		MapDraw(window, *game->map);
		window.draw(game->player->sprite);
		
		window.display();
	}
	return 0;
}
