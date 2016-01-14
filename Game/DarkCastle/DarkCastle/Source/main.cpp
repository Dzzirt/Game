#include "../Headers/game.h"
#include "../Headers/window_utils.h"
using namespace sf;



int main() {
	sf::RenderWindow * window = CreateRenderWindow();
	Game* game = CreateGame();
	Clock clock;
	Time time_since_last_update = Time::Zero;
	while (window->isOpen()) {
		ProcessEvents(game, *window);
		time_since_last_update += clock.restart();
		while (time_since_last_update > TimePerFrame) {
			time_since_last_update -= TimePerFrame;
			ProcessEvents(game, *window);
			Update(*game, TimePerFrame);
		}
		Render(*game, *window);

	}
	DestroyGame(game);
	DestroyWindow(window);
	return 0;
}



