#include <vld.h>
#include "game.h"

using namespace sf;

const Time TimePerFrame = seconds(1.f / 60.f);

int main() {
	RenderWindow window(VideoMode(800, 600), "From the Shadow of Underdark");
	Game* game = new Game();
	GameInit(*game);
	Clock clock;
	Time time_since_last_update = Time::Zero;

	while (window.isOpen()) {
		ProcessEvents(window, *game);
		time_since_last_update += clock.restart();
		while (time_since_last_update > TimePerFrame) {
			time_since_last_update -= TimePerFrame;
			ProcessEvents(window, *game);
			Update(*game, TimePerFrame);
		}
		Render(window, *game);

	}
	return 0;
}



