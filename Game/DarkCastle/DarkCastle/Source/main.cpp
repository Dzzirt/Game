#include "vld.h"
#include "../Headers/game.h"
#include <chrono>
using namespace sf;

int main() {
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	Game* game = CreateGame();
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << elapsed_seconds.count();
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
	DestroyGame(game);
	return 0;
}



