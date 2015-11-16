#include "vld.h"
#include "../Headers/game.h"

using namespace sf;

int main() {
	Game* game = new Game();
	GameInit(*game);
	Clock clock;
	Time time_since_last_update = Time::Zero;
	while (game->window->isOpen()) {
		ProcessEvents(*game);
		time_since_last_update += clock.restart();
		while (time_since_last_update > TimePerFrame) {
			time_since_last_update -= TimePerFrame;
			ProcessEvents(*game);
			Update(*game, TimePerFrame);
			
		}
		Render(*game);
	}
	return 0;
}



