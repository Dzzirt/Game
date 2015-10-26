#include "vld.h"
#include "game.h"
#include "entity_consts.h"


using namespace sf;

int main() {
	Game* game = new Game();
	GameInit(*game);
	Clock clock;
	Time time_since_last_update = Time::Zero;
	while (game->window->isOpen()) {
		ProcessEvents(*game->window, *game);
		time_since_last_update += clock.restart();
		while (time_since_last_update > TimePerFrame) {
			time_since_last_update -= TimePerFrame;
			ProcessEvents(*game->window, *game);
			Update(*game, TimePerFrame);
			
		}
		Render(*game->window, *game);

	}
	return 0;
}



